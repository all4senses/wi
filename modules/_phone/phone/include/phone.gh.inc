<?php

define('PHONE_NUMBER_PREFIX', 233);
define('PHONE_NUMBER_LENGTH', 9);

/**
 * @file
 * CCK Field for Ghana phone numbers.
 */

function phone_gh_metadata() {
  // These strings are translated using t() on output.
  return array(
    'error' => '"%value" is not a valid Ghana phone number!',
  );
}

/**
 * Verifies that $phonenumber is valid
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid.
 */
function valid_gh_phone_number($phonenumber) {
  // define regular expression
  //$regex = "/^(\+233\s+)?\d{2}(\s*|\-)\d{3}(\s*|\-)\d{4}(\s*|\-)$/i";
  // return true if valid, false otherwise
  //return (bool) preg_match($regex, $phonenumber);
  $phonenumber  = str_replace(array(' ','+','(',')','.','-'), '', $phonenumber);
  if(strlen($phonenumber) != PHONE_NUMBER_LENGTH) {
    return false;
  }
  return true;
}

/**
 * Formatting for Ghana Phone Numbers.
 *
 * @param string $phonenumber
 * @return string Returns a string containting the phone number with some formatting.
 */
function format_gh_phone_number($phonenumber, $field) {
   $phonenumber  = str_replace(array(' ','+','(',')','.','-'), '', $phonenumber);

   if(strlen($phonenumber) == PHONE_NUMBER_LENGTH)
     $phonenumber = PHONE_NUMBER_PREFIX . $phonenumber;

   return $phonenumber;
}
