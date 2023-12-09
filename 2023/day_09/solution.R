library(tidyverse)

input_raw <- read_lines(here::here("2023/day_09/input.txt"))

input <- purrr::map(
  input_raw,
  \(x) x |>
  stringr::str_split("\\s") |>
  unlist() |>
  as.numeric()
)

diff_recursion <- function(input) {
  d <- diff(input)
  
  if (all(d == 0)) {
    return(c(input, input[length(input)]))
  }

  out <- diff_recursion(d)
  c(input, input[length(input)] + out[length(out)])
}

# * Part 1
purrr::map(
  input, 
  \(x) {
    out <- diff_recursion(x)
    out[length(out)]
  }
) |>
  unlist() |>
  sum()


# * Part 2
purrr::map(
  input, 
  \(x) {
    out <- diff_recursion(rev(x))
    out[length(out)]
  }
) |>
  unlist() |>
  sum()

