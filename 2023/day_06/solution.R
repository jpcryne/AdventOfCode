# * Read input
input <- read_lines(here::here("2023/day_06/input.txt")) |>
  stringr::str_extract_all("\\d+") |>
  as.data.frame() |>
  set_names(c("time", "record")) |>
  dplyr::mutate(
    id = dplyr::row_number(),
    dplyr::across(c(time, record), as.numeric)
  )

# * Part 1
input |>
  dplyr::cross_join(data.frame(hold = 0:max(input$time))) |>
  dplyr::filter(hold <= time) |>
  dplyr::mutate(
    result = (time - hold) * hold
  ) |>
  dplyr::filter(result > record) |>
  dplyr::summarise(
    n = dplyr::n(),
    .by = id
  ) |>
  dplyr::pull(n) |>
  prod()
  
# * Part 2
input2 <- input |>
  dplyr::reframe(
    dplyr::across(c(time, record), \(x) paste0(x, collapse = ""))
  ) |>
  dplyr::mutate(
    id = dplyr::row_number(),
    dplyr::across(c(time, record), as.numeric)
  )

input2 |>
  dplyr::cross_join(data.frame(hold = 0:max(input2$time))) |>
  dplyr::filter(hold <= time) |>
  dplyr::mutate(
    result = (time - hold) * hold
  ) |>
  dplyr::filter(result > record) |>
  dplyr::summarise(
    n = dplyr::n(),
    .by = id
  ) |>
  dplyr::pull(n) |>
  prod()

