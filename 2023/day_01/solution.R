input <- read.delim(here::here("2023/day_01/input.txt"), header = FALSE)

# * Part 1
input |>
  dplyr::mutate(
    calibration_code = gsub("[A-z]", "", V1),
    calibration_code = sapply(calibration_code, \(x) as.integer(paste0(substring(x, 1, 1), substring(x, nchar(x), nchar(x)))))
  ) |>
  dplyr::summarise(sum(calibration_code))

# * Part 2
input |>
  dplyr::mutate(
    first_digit = stringi::stri_extract_first_regex(V1, paste0(c("[1-9]", xfun::numbers_to_words(1:9)), collapse = "|")),
    last_digit = stringi::stri_extract_first_regex(
      stringi::stri_reverse(V1), 
      stringi::stri_reverse(paste0(c("]9-1[", xfun::numbers_to_words(1:9)), collapse = "|"))
    ) |>
      stringi::stri_reverse(),
    first_digit = sapply(first_digit, \(x) ifelse(nchar(x) == 1, as.integer(x), which(xfun::n2w(1:9) == x))), 
    last_digit = sapply(last_digit, \(x) ifelse(nchar(x) == 1, as.integer(x), which(xfun::n2w(1:9) == x))),
    calibration_code = as.integer(paste0(first_digit, last_digit))
  ) |>
   dplyr::summarise(sum(calibration_code))
