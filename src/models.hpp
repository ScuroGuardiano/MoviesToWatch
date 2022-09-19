#pragma once

#include <string>
#include <vector>

enum class MovieType
{
  Movie = 1,
  Anime,
  AnimeMovie,
  Series
};

class Movie
{
public:
  uint64_t id = 0;
  std::string name;
  MovieType type = MovieType::Movie;
  uint32_t priority = 0;
  uint16_t year = 0;
  std::vector<std::string> tags;
};
