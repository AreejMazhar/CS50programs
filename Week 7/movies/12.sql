SELECT title
FROM movies
JOIN stars on stars.movie_id = movies.id
JOIN people on people.id = stars.person_id
WHERE people.name = 'Bradley Cooper'
AND title IN (
    SELECT title
    FROM movies
    JOIN stars on stars.movie_id = movies.id
    JOIN people on people.id = stars.person_id
    WHERE people.name = 'Jennifer Lawrence'
);