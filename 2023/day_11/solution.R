library(tidyverse)

input_raw <- read_lines(here::here("2023/day_11/input.txt")) 

input_tmp <- purrr::map(
  input_raw,
  \(x) stringr::str_locate_all(string = x, pattern = '#')[[1]][, 1]
)
  
input <- purrr::map(
  1:length(input_raw),
  \(i) {
    if (length(input_tmp[[i]]) > 0) {
      d <- data.frame(x = i, y = input_tmp[[i]])
    } else {
      d <- data.frame(x = numeric(0), y = numeric(0))
    }
    d
  }
) |>
  purrr::list_rbind() |>
  dplyr::mutate(id = row_number())

expand_rows <- function(df, n = 1) {
  for (i in length(input_raw):1) {
    if (length(which(df$x == i)) == 0) {
      df <- df |>
        dplyr::mutate(x = dplyr::if_else(x > !!i, x + !!n, x))
    }
  }
  df
}

expand_cols <- function(df, n = 1) {
  for (j in nchar(input_raw[[1]]):1) {
    if (length(which(df$y == j)) == 0) {
      df <- df |>
        dplyr::mutate(y = dplyr::if_else(y > !!j, y + !!n, y))
    }
  }
  df
}

# * Part 1
p1 <- input
# * Expand rows
p1 <- expand_rows(p1)

# * Expand columns
p1 <- expand_cols(p1)

# * Calculate shortest paths
p1 |>
  dplyr::cross_join(p1, suffix = c(".start", ".end")) |>
  dplyr::filter(id.start < id.end) |>
  # * Calculate Manhattan Distance
  dplyr::mutate(distance = abs(x.start - x.end) + abs(y.start - y.end)) |>
  dplyr::pull(distance) |>
  sum()

# * Part 2
p2 <- input

p2 <- expand_rows(p2, n = 999999)
p2 <- expand_cols(p2, n = 999999)

p2 |>
  dplyr::cross_join(p2, suffix = c(".start", ".end")) |>
  dplyr::filter(id.start < id.end) |>
  # * Calculate Manhattan Distance
  dplyr::mutate(distance = abs(x.start - x.end) + abs(y.start - y.end)) |>
  dplyr::pull(distance) |>
  sum()

