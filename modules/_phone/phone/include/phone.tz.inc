<?php

/**
 * @file
 * CCK Field for Tanzania phone numbers.
 */

function phone_tz_metadata() {
  // These strings are translated using t() on output.
  return array(
    'error' => '"%value" is not a valid Tanzania phone number!',
  );
}

/**
 * Verifies that $phonenumber is valid
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid.
 */
function valid_tz_phone_number($phonenumber) {
  // define regular expression
  $regex = "/^(\+255\s+)?\d{2}(\s*|\-)\d{3}(\s*|\-)\d{4}(\s*|\-)$/i";
  // return true if valid, false otherwise
  return (bool) preg_match($regex, $phonenumber);
}

/**
 * Formatting for Tanzania Phone Numbers.
 *
 * @param string $phonenumber
 * @return string Returns a string containting the phone number with some formatting.
 */
function format_tz_phone_number($phonenumber, $field) {
   $phonenumber  = str_replace(array(' ','+','(',')','.','-'), '', $phonenumber);

   if(strlen($phonenumber) < 9)
       $phonenumber = '255' . $phonenumber;

   return $phonenumber;
}
