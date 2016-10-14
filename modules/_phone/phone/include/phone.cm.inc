<?php

define('PHONE_NUMBER_PREFIX', 237);
define('PHONE_NUMBER_LENGTH', 8);

/**
 * @file
 * CCK Field for Cameroon phone numbers.
 */

function phone_cm_metadata() {
  // These strings are translated using t() on output.
  return array(
    'error' => '"%value" is not a valid Cameroon phone number!',
  );
}

/**
 * Verifies that $phonenumber is valid
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid.
 */
function valid_cm_phone_number($phonenumber) {
  // define regular expression
  //$regex = "/^(\+237\s+)?\d{4}(\s*|\-)\d{4}(\s*|\-)$/i";
  // return true if valid, false otherwise
  //return (bool) preg_match($regex, $phonenumber);
  $phonenumber  = str_replace(array(' ','+','(',')','.','-'), '', $phonenumber);
  if(strlen($phonenumber) != PHONE_NUMBER_LENGTH) {
    return false;
  }
  return true;
}

/**
 * Formatting for Cameroon Phone Numbers.
 *
 * @param string $phonenumber
 * @return string Returns a string containting the phone number with some formatting.
 */
function format_cm_phone_number($phonenumber, $field) {
   $phonenumber  = str_replace(array(' ','+','(',')','.','-'), '', $phonenumber);

   if(strlen($phonenumber) == PHONE_NUMBER_LENGTH)
       $phonenumber = PHONE_NUMBER_PREFIX . $phonenumber;

   return $phonenumber;
}
