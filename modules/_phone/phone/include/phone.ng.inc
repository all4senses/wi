<?php

/**
 * @file
 * CCK Field for Nigerian phone numbers.
 */

function phone_ng_metadata() {
  // These strings are translated using t() on output.
  return array(
    'error' => '"%value" is not a valid Nigerian mobile phone number<br>Nigerian phone numbers should only ...',
  );
}

/**
 * Verifies that $phonenumber is valid
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid.
 */
function valid_ng_phone_number($phonenumber) {
  // define regular expression
  $regex = "/^(((\+234\s+|234)?(\()?\d{2}(\))?(\s*))|(0\d{2}))\d{7,8}$/i";

  // return true if valid, false otherwise
  return (bool) preg_match($regex, $phonenumber);
}

/**
 * Formatting for Nigerian Phone Numbers.
 *
 * @param string $phonenumber
 * @return string Returns a string containting the phone number with some formatting.
 */
function format_ng_phone_number($phonenumber, $field) {
   $phonenumber  = str_replace(array(' ','+','(',')','.','-'), '', $phonenumber);

   if(strlen($phonenumber) < 12)
       $phonenumber = '234' . $phonenumber;

   return $phonenumber;
}
