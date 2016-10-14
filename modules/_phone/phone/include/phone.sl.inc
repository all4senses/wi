<?php

define('PHONE_NUMBER_PREFIX', 232);
define('PHONE_NUMBER_LENGTH', 8);

/**
 * @file
 * CCK Field for Sierra Leone phone numbers.
 */

function phone_sl_metadata() {
  // These strings are translated using t() on output.
  return array(
    'error' => '"%value" is not a valid Sierra Leone phone number!',
  );
}

/**
 * Verifies that $phonenumber is valid
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid.
 */
function valid_sl_phone_number($phonenumber) {
  // define regular expression
  //$regex = "/^(\+232\s+)?\d{2}(\s*|\-)\d{3}(\s*|\-)\d{3}(\s*|\-)$/i";
  // return true if valid, false otherwise
  //return (bool) preg_match($regex, $phonenumber);
  $phonenumber  = str_replace(array(' ','+','(',')','.','-'), '', $phonenumber);
  if(strlen($phonenumber) != PHONE_NUMBER_LENGTH) {
    return false;
  }
  return true;
}

/**
 * Formatting for Sierra Leone Phone Numbers.
 *
 * @param string $phonenumber
 * @return string Returns a string containting the phone number with some formatting.
 */
function format_sl_phone_number($phonenumber, $field) {
   $phonenumber  = str_replace(array(' ','+','(',')','.','-'), '', $phonenumber);

   if(strlen($phonenumber) == PHONE_NUMBER_LENGTH)
       $phonenumber = PHONE_NUMBER_PREFIX . $phonenumber;

   return $phonenumber;
}
