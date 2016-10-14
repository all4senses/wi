<?php

/**
 * @file
 * CCK Field for Togo phone numbers.
 */

function phone_tg_metadata() {
  // These strings are translated using t() on output.
  return array(
    'error' => '"%value" is not a valid Togo phone number!',
  );
}

/**
 * Verifies that $phonenumber is valid
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid.
 */
function valid_tg_phone_number($phonenumber) {
  // define regular expression
  $regex = "/^(\+228\s+)?\d{2}(\s*|\-)\d{2}(\s*|\-)\d{2}(\s*|\-)\d{2}$/i";
  // return true if valid, false otherwise
  return (bool) preg_match($regex, $phonenumber);
}

/**
 * Formatting for Togo Phone Numbers.
 *
 * @param string $phonenumber
 * @return string Returns a string containting the phone number with some formatting.
 */
function format_tg_phone_number($phonenumber, $field) {
   $phonenumber  = str_replace(array(' ','+','(',')','.','-'), '', $phonenumber);

   if(strlen($phonenumber) < 8)
       $phonenumber = '228' . $phonenumber;

   return $phonenumber;
}
