<?php

define('PHONE_NUMBER_PREFIX', 231);
define('PHONE_NUMBER_LENGTH_MIN', 7);
define('PHONE_NUMBER_LENGTH_MAX', 8);

/**
 * @file
 * CCK Field for Liberia phone numbers.
 */

function phone_lr_metadata() {
  // These strings are translated using t() on output.
  return array(
    'error' => '"%value" is not a valid Liberia phone number!',
  );
}

/**
 * Verifies that $phonenumber is valid
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid.
 */
function valid_lr_phone_number($phonenumber) {
  // define regular expression
  //$regex = "/^(\+231\s+)?\d{4}(\s*|\-)\d{3,4}(\s*|\-)$/i";
  // return true if valid, false otherwise
  //return (bool) preg_match($regex, $phonenumber);
  $phonenumber  = str_replace(array(' ','+','(',')','.','-'), '', $phonenumber);
  if(strlen($phonenumber) >= PHONE_NUMBER_LENGTH_MIN && strlen($phonenumber) <= PHONE_NUMBER_LENGTH_MAX) {
    return true;
  }
  return false;
}

/**
 * Formatting for Liberia Phone Numbers.
 *
 * @param string $phonenumber
 * @return string Returns a string containting the phone number with some formatting.
 */
function format_lr_phone_number($phonenumber, $field) {
   $phonenumber  = str_replace(array(' ','+','(',')','.','-'), '', $phonenumber);

   if(strlen($phonenumber) >= PHONE_NUMBER_LENGTH_MIN && strlen($phonenumber) <= PHONE_NUMBER_LENGTH_MAX)
       $phonenumber = PHONE_NUMBER_PREFIX . $phonenumber;

   return $phonenumber;
}
