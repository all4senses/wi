<?php

define('PHONE_NUMBER_PREFIX', 225);
define('PHONE_NUMBER_LENGTH', 8);

/**
 * @file
 * CCK Field for Ivory Coast phone numbers.
 */

function phone_ci_metadata() {
  // These strings are translated using t() on output.
  return array(
    'error' => '"%value" is not a valid Ivory Coast phone number!',
  );
}

/**
 * Verifies that $phonenumber is valid
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid.
 */
function valid_ci_phone_number($phonenumber) {
  // define regular expression
  //$regex = "/^(\+225\s+)?\d{2}(\s*|\-)\d{2}(\s*|\-)\d{2}(\s*|\-)\d{2}$/i";
  // return true if valid, false otherwise
  //return (bool) preg_match($regex, $phonenumber);
  $phonenumber  = str_replace(array(' ','+','(',')','.','-'), '', $phonenumber);
  if(strlen($phonenumber) != PHONE_NUMBER_LENGTH) {
    return false;
  }
  return true;
}

/**
 * Formatting for Ivory Coast Phone Numbers.
 *
 * @param string $phonenumber
 * @return string Returns a string containting the phone number with some formatting.
 */
function format_ci_phone_number($phonenumber, $field) {
   $phonenumber  = str_replace(array(' ','+','(',')','.','-'), '', $phonenumber);

   if(strlen($phonenumber) == PHONE_NUMBER_LENGTH)
       $phonenumber = PHONE_NUMBER_PREFIX . $phonenumber;

   return $phonenumber;
}
