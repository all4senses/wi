<?php

/**
 * @file
 * CCK Field for Namibia phone numbers.
 */

function phone_na_metadata() {
  // These strings are translated using t() on output.
  return array(
    'error' => '"%value" is not a valid Namibia phone number!',
  );
}

/**
 * Verifies that $phonenumber is valid
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid.
 */
function valid_na_phone_number($phonenumber) {
  // define regular expression
  $regex = "/^(\+264\s+)?\d{2}(\s*|\-)\d{3}(\s*|\-)\d{3}(\s*|\-)$/i";
  // return true if valid, false otherwise
  return (bool) preg_match($regex, $phonenumber);
}

/**
 * Formatting for Namibia Phone Numbers.
 *
 * @param string $phonenumber
 * @return string Returns a string containting the phone number with some formatting.
 */
function format_na_phone_number($phonenumber, $field) {
   $phonenumber  = str_replace(array(' ','+','(',')','.','-'), '', $phonenumber);

   if(strlen($phonenumber) < 9)
       $phonenumber = '264' . $phonenumber;

   return $phonenumber;
}
