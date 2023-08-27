-- Keep a log of any SQL queries you execute as you solve the mystery.

-- What we know:
-- date: July 28, 2021
-- place: Humphrey Street

-- Any data from crime scene reports about the crime
SELECT description
FROM crime_scene_reports
WHERE year = 2021 AND month = 7 AND day = 28 AND street = 'Humphrey Street';
-- 10:15am, interviews with three witnesses that mention bakery

-- Info about the interviews
SELECT id, name, transcript
FROM interviews
WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE '%bakery%';
-- 161, Ruth, Bakery parking lot, left sometime within 10 minutes of the theft (check security footage)
-- 162, Eugene, Someone he recognized, ATM on Leggett Street and theif withdrawing money earlier this morning
-- 163, Raymond, Thief leaving the bakery, called someone and talked for less than a minute, planning on taking the earliest flight out of fiftyville tomorrow (29 July). Accomplice bought the flight ticket

-- Eugene said: Thief was withdrawing money from the ATM on Leggett Street
SELECT account_number, amount
FROM atm_transactions
WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'
ORDER BY amount ASC;

--Find the names associated with the accounts, now suspects
SELECT name, atm_transactions.amount FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_transactions.year = 2021 AND atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_transactions.atm_location = 'Leggett Street' AND atm_transactions.transaction_type = 'withdraw'
ORDER BY atm_transactions.amount ASC;
-- Suspects: Kenny, Iman, Benista, Diana, Luca, Bruce, Taylor, Brooke

-- Raymond said: Thief leaving the bakery, called someone and talked for less than a minute, taking the earliest flight out of fiftyville tomorrow (29 July)
-- Accomplice bought the flight ticket
--Find info about Fiftyville airport (origin destination of the theif)
SELECT id, abbreviation, full_name
FROM airports
WHERE city = 'Fiftyville';

--Finding the flights on July 29 from Fiftyville airport, order by time
SELECT flights.id, full_name, city, flights.hour, flights.minute FROM airports
JOIN flights ON airports.id = flights.destination_airport_id
WHERE flights.origin_airport_id = (
SELECT id FROM airports
WHERE city = 'Fiftyville') AND flights.year = 2021 AND flights.month = 7 AND flights.day = 29
ORDER BY flights.hour, flights.minute;
--earliest flight is LaGaurdia Airport, to New York City, At 8:20am, flight id 36

--Checking passengers on the flight. Order by passport number
SELECT passengers.flight_id, name, passengers.passport_number, passengers.seat FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
WHERE flights.year = 2021 AND flights.month = 7 AND flights.day = 29 AND flights.hour = 8 AND flights.minute = 20
ORDER BY passengers.passport_number;
--Suspects: Edward, Sofia, Taylor, Bruce, Doris, Kelsey, Luca, Kenny
--Names overlap: Kenny, Luca, Bruce, Taylor

--call logs, checking the caller. Order by duration of call.
SELECT name, phone_calls.duration FROM people
JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE phone_calls.year = 2021 AND phone_calls.month = 7 AND phone_calls.day = 28 AND phone_calls.duration <= 60
ORDER BY phone_calls.duration;
--Suspects: Kelsey, Carina, Taylor, Bruce, Diana, Sofia, Benista, Kenny, Kathryn

--call logs, checking the reciver. Ordr by duration of call
SELECT name, phone_calls.duration FROM people
JOIN phone_calls ON people.phone_number = phone_calls.receiver
WHERE phone_calls.year = 2021 AND phone_calls.month = 7 AND phone_calls.day = 28 AND phone_calls.duration <= 60
ORDER BY phone_calls.duration;
--Suspects (Accomplices): Larry, Jacqueline, James, Robin, Philip, Melissa, Jack, Anna, Doris, Luca

--Ruth said: Bakery parking lot, left sometime within 10 minutes of the theft (check security footage)
SELECT name, bakery_security_logs.hour, bakery_security_logs.minute FROM people
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE bakery_security_logs.year = 2021 AND bakery_security_logs.month = 7 AND bakery_security_logs.day = 28 AND bakery_security_logs.activity = 'exit' AND bakery_security_logs.hour = 10 AND bakery_security_logs.minute >= 15 AND bakery_security_logs.minute <= 25
ORDER BY bakery_security_logs.minute;
--Suspects: Vanessa, Bruce, Barry, Luca, Sofia, Iman, Diana, Kelsey
--Overlap: Bruce

--Conclusion:
--Bruce must be the theif as he's in all four lists (Atm transactions, the one who called, the one who drove away, the passengers)
--He must be in New York City, it was the earliest flight the next day from Fiftyville
--The accomplice is Robin, as everyone else is accounted for.