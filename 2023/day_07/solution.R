library(tidyverse)
input_raw <- read_lines(here::here("2023/day_07/input.txt")) |>
  stringr::str_split("\\s+") |>
  unlist() |>
  matrix(ncol = 2, byrow = T) |>
  data.frame() |>
  set_names(c("hand", "bet")) 

# * Part 1
input <- input_raw |>
  dplyr::mutate(
    hand_split = stringr::str_split(hand, ""),
    hand_split = purrr::map(
      hand_split, 
      \(x) {
        x |>
          stringr::str_replace_all("T", "10") |>
          stringr::str_replace_all("J", "11") |>
          stringr::str_replace_all("Q", "12") |>
          stringr::str_replace_all("K", "13") |>
          stringr::str_replace_all("A", "14") |>
          as.numeric()
          
      }
    ),
    hand_breakdown = purrr::map(
      hand_split,
      \(x) {
        x |>
          table() |>
          as.numeric() |>
          sort(decreasing = T)
      }
    ),
    hand_type = purrr::map(
      hand_breakdown,
      \(x) dplyr::case_when(
        length(x) == 1 ~ 7,
        length(x) == 2 && all(x == c(4, 1)) ~ 6,
        length(x) == 2 && all(x == c(3, 2)) ~ 5,
        length(x) == 3 && all(x == c(3, 1, 1)) ~ 4,
        length(x) == 3 && all(x == c(2, 2, 1)) ~ 3,
        length(x) == 4 ~ 2,
        length(x) == 5 ~ 1,
        TRUE ~ 0
      )
    ) |>
      unlist()
  ) |>
  unnest_wider(hand_split, names_sep = "_") |>
  dplyr::arrange(
    hand_type, hand_split_1, hand_split_2, hand_split_3, hand_split_4, hand_split_5
  ) |>
  dplyr::mutate(
    rank = row_number(),
    points = rank * as.numeric(bet)
  ) |>
  dplyr::pull(points) |>
  sum()

# * Part 2
input <- input_raw |>
  dplyr::mutate(
    hand_original = hand,
    hand_split_original = stringr::str_split(hand_original, ""),
    hand_split_original = purrr::map(
      hand_split_original, 
      \(x) {
        x |>
          stringr::str_replace_all("T", "10") |>
          stringr::str_replace_all("J", "0") |>
          stringr::str_replace_all("Q", "12") |>
          stringr::str_replace_all("K", "13") |>
          stringr::str_replace_all("A", "14") |>
          as.numeric()
        
      }
    ),
    hand = stringr::str_replace_all(hand, "J", ""),
    hand_split = stringr::str_split(hand, ""),
    hand_split = purrr::map(
      hand_split, 
      \(x) {
        x |>
          stringr::str_replace_all("T", "10") |>
          stringr::str_replace_all("J", "11") |>
          stringr::str_replace_all("Q", "12") |>
          stringr::str_replace_all("K", "13") |>
          stringr::str_replace_all("A", "14") |>
          as.numeric()
        
      }
    ),
    hand_breakdown = purrr::map(
      hand_split,
      \(x) {
        out <- x |>
          table() |>
          as.numeric() |>
          sort(decreasing = T)
        # * Add the jokers in as the most common card
        if (sum(out) < 5) {
          out[1] <- out[1] + (5 - sum(out))
        }
        out
      }
    ),
    hand_type = purrr::map(
      hand_breakdown,
      \(x) dplyr::case_when(
        length(x) == 1 ~ 7,
        length(x) == 2 && all(x == c(4, 1)) ~ 6,
        length(x) == 2 && all(x == c(3, 2)) ~ 5,
        length(x) == 3 && all(x == c(3, 1, 1)) ~ 4,
        length(x) == 3 && all(x == c(2, 2, 1)) ~ 3,
        length(x) == 4 ~ 2,
        length(x) == 5 ~ 1,
        TRUE ~ 0
      )
    ) |>
      unlist()
  ) |>
  unnest_wider(hand_split_original, names_sep = "_") |>
  dplyr::arrange(
    hand_type, hand_split_original_1, hand_split_original_2, hand_split_original_3, hand_split_original_4, hand_split_original_5
  ) |>
  dplyr::mutate(
    rank = row_number(),
    points = rank * as.numeric(bet)
  )

input |>
  dplyr::pull(points) |>
  sum()
