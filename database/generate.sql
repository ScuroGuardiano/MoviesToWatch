CREATE TYPE movie_type AS ENUM('movie', 'anime', 'anime_movie', 'series');

CREATE TABLE IF NOT EXISTS users (
    id uuid DEFAULT uuid_generate_v4() PRIMARY KEY,
    username VARCHAR(32) UNIQUE NOT NULL,
    password VARCHAR(64) NOT NULL
);

CREATE TABLE IF NOT EXISTS movies (
    id serial PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    year SMALLINT,
    type movie_type DEFAULT 'movie',
    genre VARCHAR(32),
    episode_count SMALLINT DEFAULT 1 NOT NULL,
    avg_duration_per_episode INT
);

CREATE TABLE IF NOT EXISTS movies_to_watch (
    id serial PRIMARY KEY,
    priority INT DEFAULT 1 NOT NULL,
    movie_id INT NOT NULL,
    comment TEXT
);

CREATE TABLE IF NOT EXISTS movies_watched (
    id serial PRIMARY KEY,
    rating SMALLINT,
    movie_id INT NOT NULL,
    comment TEXT
);