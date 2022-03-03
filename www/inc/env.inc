<?php

    // Report all errors except E_NOTICE.
    // To reduce log file size.
error_reporting (E_ALL ^ E_NOTICE);


    // Include this file before any other include files.
    //
    // This file defines function for retrieving data from
    // GET, POST, Cookies.

/* MODS:
 *  2007-07-28, Hong Zhang
 *      # $_unlvlib_ip_range_[_IP_LIB_ADMIN_] has been added more ip ranges:
 *          From 131.216.162.* to 131.216.169.*
 *          Added 10.249.248.*, for VPN users.
 *      # Added $_VALID_FILE_EXTS_, to be used for restricting access to
 *        certain files on our server, currently used by "index.php" under
 *        /staffgo/documents/ and /staffgo/admin_docs/.
 */

    /* NOTE: this function is deprecated, and magic_quotes_runtime has been
     *       set to Off explicitely in php.ini.
     *       Therefore, no need for this function anymore.
     */
// We don't want any PHP function to escape anything, either
// from database or file.
// So disable magic_quotes_runtime, no matter what the PHP configuration
// is in "php.ini".
//set_magic_quotes_runtime(0);

// Define how PHP escapes GPC data.
// We use ENT_QUOTES to escape both single/double quotes.
//define( "_PHP_QUOTE_STYLE_", ENT_COMPAT);
define( "_PHP_QUOTE_STYLE_", ENT_QUOTES);
//define( "_PHP_QUOTE_STYLE_", ENT_NOQUOTES);


// Define encoding for functions: htmlentities(), html_entity_decode() and htmlspecialchars().
// Use ISO-8859-1.
//define( "_PHP_ENCODING_", 'ISO-8859-1');
define( "_PHP_ENCODING_", 'UTF-8');


    // Must reset document root to be within '/static' folder.
    // That's the default root for all static files.
if ( ! strstr ($_SERVER["DOCUMENT_ROOT"], '/static' ) )
    $_SERVER["DOCUMENT_ROOT"] .= '/static';

    // Remove '/static' if it exists, so that following links
    // don't have the string.
$_SERVER["PHP_SELF"] = str_replace ('/static', '', $_SERVER["PHP_SELF"]);
// Declare as global in functions where you want to use it.
$_phpself_ = $_SERVER["PHP_SELF"];


    // 2007-07-28, Hong Zhang
    // Only display files with extensions defined in this array.
    // All in lower cases.
$_VALID_FILE_EXTS_ = array (
    "doc", "pdf", "txt", "xls", "psd", "ppt", "html", "htm", "jpg", "jpeg", "gif", "wmv", "xlsx", "docx", "pptx"
);

    // To be included and used by database administration script only.
    // This file defines the IP address range that is allowed
    // to access the database administration web page.
    // Scripts can check $_SERVER["REMOTE_ADDR"] to make
    // sure that page request comes from the correct IP.
    // MUST use pattern matching.
define ("_IP_LIB_ADMIN_", 1);

$_unlvlib_ip_range_ = array (
    _IP_LIB_ADMIN_  => array (
//            "131.216.16[2-9].",
            "192.168.0.",
            "192.168.1.",
            "192.168.2.",
            "192.168.3.",
            "192.168.4.",
            "::1",


// New ip ranges, from trespass system.
        '131.216.168.',     // Lied & branches, staff
        '131.216.164.',     // Lied & branches, staff
        '131.216.162.',     // Lied & branches
        '10.249.248.',      // VPN

            // all below are per Don Castle
        '131.216.172.',     // Law
        '131.216.173.',     // Law (confirmed by Emilie M.)
        '131.216.174.',     // Law

            // 20150126, Now Law School is all under 10.* subnet.
        '10.21.4.',
        '10.21.5.',
        '10.21.12.',
        '10.21.13.',

            // 20180404, HSL
        '10.22.10.47',      // HSL IC Circ6
        '10.22.11.44',      // HSL IC Circ4
        '10.23.8.58',       // Katie
        '10.23.8.126',      // HSL Lib Circ1
        '10.23.8.130',      // Marice

        '10.23.8.166',      // Mellanye Lackey
        '10.82.252.33',     // Mellanye Lackey
'173.244.217.54', // Mellanye Lackey, BUT MUST FIX THE PROBLEM ASAP

        '10.23.9.9',        // Cory
        '10.23.9.40',       // HSL Lib Circ2


            // 20190808, switched to campus VPN.
        '10.240.36.',        // 10.240.36.0/24


//        '10.82.96.124',     // Rebecca

    )
);

    // Define signal tag for string transformation.
    // Meaning of encode and decode varies depending on context.
define ("_ENCODE_", 0);       // Encode the string.
define ("_DECODE_", 1);       // Decode the string.


    // Define data validation type.
    // Can initialize to _CHECK_ANY_VAL_, then functions can change it
    // to other type.
define ("_CHECK_EMPTY_VAL_", 1);    // Invalid data if value is empty.
define ("_CHECK_ANY_VAL_", 2);      // If data value is empty, just skip check.
    
    // Define GPC kay names for all variables.
define( "_GPC_NAME_", "name" );         // Descriptive name.
define( "_GPC_VALUE_", "value" ); 
define( "_GPC_MIN_VAL_", "minVal" );    // The minimum value, for number only.
define( "_GPC_MAX_VAL_", "maxVal" );    // The maximum value, for number only.
define( "_GPC_MIN_LEN_", "minLen" );    // The minimum length.
define( "_GPC_MAX_LEN_", "maxLen" );    // The maximum length.
define( "_GPC_PATTERN_", "pattern" );   // The pattern string for regular expr.
define ("_GPC_CHECK_TYPE_", "checktype");   // Do we check empty value?


    // Define HTML meta tags.
    // This is define as: pattern => replacement, for preg_replace().
    // Need to use foreach().
$_HTML_META_TAGS_ = array ( "/\[BOLD\]/i"        => "<b>",
                            "/\[\/BOLD\]/i"      => "</b>",
                            "/\[ITALIC\]/i"      => "<i>",
                            "/\[\/ITALIC\]/i"    => "</i>",
                            "/\[UNDERLINE\]/i"   => "<u>",
                            "/\[\/UNDERLINE\]/i" => "</u>",
                            "/\[\/URL\]/i"       => "</a>",
                            "/\[URL=(.*?)\]/i"  => "<a href=\"\$1\">",

                            "/\[\/NAME\]/i"       => "</a>",
                            "/\[NAME=(.*?)\]/i"  => "<a name=\"\$1\">"
                          );


    // Define HTML meta tags.
    // This is define as: pattern => replacement, for preg_replace().
    // Do not use foreach.
$_HTML_META_TAGS_PAT_ = array ( 0 => "/\[BOLD\]/i",
                                1 => "/\[\/BOLD\]/i",
                                2 => "/\[ITALIC\]/i",
                                3 => "/\[\/ITALIC\]/i",
                                4 => "/\[UNDERLINE\]/i",
                                5 => "/\[\/UNDERLINE\]/i",
                                6 => "/\[\/URL\]/i",
                                7 => "/\[URL=(.*?)\]/i",
                                8 => "/&amp;reg;/i",

                                9 => "/\[\/NAME\]/i",
                                10 => "/\[NAME=(.*?)\]/i"
                              );

$_HTML_META_TAGS_REPLACE_ = array ( 0 => "<b>",
                                    1 => "</b>",
                                    2 => "<i>",
                                    3 => "</i>",
                                    4 => "<u>",
                                    5 => "</u>",
                                    6 => "</a>",
                                    7 => "<a href=\"\$1\">",
                                    8 => "&reg;",

                                    9 => "</a>",
                                    10 => "<a name=\"\$1\">"

                                  );

//================================================================
function
_GetGPCData_ ($key)
// Get user input from web form.
// Decode HTML entities whatsoever, since we want to store normal
// characters into our database, rather than HTML equivalents.
// $key is the name from web form input field.
// Return an array if input is an array, else return a string.
//
// NOTE: the current implementation does not resist some attacks.
//       Should pass another parameter to this function, e.g. what data type
//       is expected for $key, string or array.
// But let's keep it this way right now, not to break existing code.
{
    $is_get = FALSE;

    // This is not really needed. But it gives us less error message.
    if ( !array_key_exists ($key, $_REQUEST) )
        return "";

    // Check if a GET request, by checking if the $key also exists in $_GET.
    // If get, then need to urldecode.
    if ( array_key_exists ($key, $_GET) )
        $is_get = TRUE;

    // Declare a signal for array.
    $isArray = FALSE;

    // Declare space for input.
    $input = array ();

    if ( is_array ($_REQUEST["$key"]) )
    {
        $isArray = TRUE;

        foreach ( $_REQUEST["$key"] as $value )
            $input[] = trim ($value);
    }
    else
        // Get single input from web form.
        $input[] = trim( $_REQUEST["$key"] );

    // Test if magic_quotes_gpc is on or off.
//    $quotStat = get_magic_quotes_gpc ();

    // Perform additional treatment to each element in input array.
    for ( $count = 0; $count < count ($input); $count++ )
    {
//        if ( $quotStat )
            // It's on, so we need to un-escape user input from web form.
            $input[$count] = stripslashes( $input[$count] );

        // Decode any HTML entities in user input and return the string.
        // PHP_QUOTE_STYLE defines whether we need to
        // decode double and single quotes.
        // Please refer to PHP manual for the meaning of that parameter.

// >> Commented out 2006-08-11, by Hong Zhang
//        if ( $is_get )
//            $input[$count] = urldecode ($input[$count]);
// << Commented out 2006-08-11, by Hong Zhang

        $input[$count] = html_entity_decode( $input[$count], _PHP_QUOTE_STYLE_, _PHP_ENCODING_ );
    }

    if ( $isArray )
        return $input;
    else
        return $input[0];
}

//================================================================
function
_ValidGPCData_ ( &$mixed, &$err )
// Validate $mixed.
// Return TRUE if $mixed is valid, else return FALSE and set $err.
// $mixed is an array containing elements of the following format:
//
//     "variable name" => array ( <'name'> => "string",
//                                <'value'> => GetGPCData ("string"),
//                                <check_type> => checking type
//                                ['min_value'] => <number>,
//                                ['max_value'] => <number>,
//                                ['min_length'] => <number>,
//                                ['max_length'] => <number>,
//                                ['pattern'] => array ( "pattern1" => err1,
//                                                       ["pattern2"] => err2,
//                                                       ...
//                                                     ),
//                              )
//
// <'value'> could be string or array.
// The keys and corresponding values in "<, >" pairs are mandatory.
// The keys and corresponding values in "[, ]" pairs are optional.
// Keys are defined above.
// All values are used for validating purpose.
// The data value must satisfy all criteria, else is invalid.
// Pattern is used by preg_match, and the value must match all patterns,
// if not, preg_match will return FALSE.
// Later on, should add negative matching.
//
// An example is shown below:
// Storage for record id number.
//    GPC_REC_ID => array ( _GPC_NAME_    => "Record ID",
//                          _GPC_VALUE_   => GetGPCData (GPC_REC_ID),
//                          _GPC_CHECK_TYPE_ => _CHECK_ANY_VAL_,
//                          _GPC_MIN_VAL_ => 0,
//                          _GPC_MAX_VAL_ => 8388607,
//                          _GPC_MIN_LEN_ => 1,
//                          _GPC_MAX_LEN_ => 7,
//                          _GPC_PATTERN_ => array ( "/^[0-9]{1,7}$/" => "must be all digits" ),
//                        ),
//
// See global definition file for more details.
{
    $result = TRUE;         // Assume no error so far.
    $err = "";

    foreach ( $mixed as $var => $data )
    {
        // If data is not array, move it into an array.
        if ( !is_array ($data[_GPC_VALUE_]) )
            $data[_GPC_VALUE_] = array ($data[_GPC_VALUE_]);

        // Check if no value at all.
        if ( $data[_GPC_CHECK_TYPE_] == _CHECK_EMPTY_VAL_
             && count ($data[_GPC_VALUE_]) <= 0 )
        {
            $result = FALSE;
            $err .= '<strong>"' . $data[_GPC_NAME_] . '"</strong>' . " can not be empty.<br>";
            continue;
        }

        // Got some value, but need to check each of them.
        // Validate each value element.
        foreach ( $data[_GPC_VALUE_] as $value )
        {
            if ( $data[_GPC_CHECK_TYPE_] == _CHECK_EMPTY_VAL_
                 && $value == "" )
            {
                $result = FALSE;
                $err .= '<strong>"' . $data[_GPC_NAME_] . '"</strong>' . " can not be empty.<br>";
                continue 2;
            }
            else if ( $data[_GPC_CHECK_TYPE_] == _CHECK_ANY_VAL_
                      && $value == "" )
                // Just skip checking, and do nothing else.
                continue 2;
            else
                // Up to here, value must not be empty, and we
                // must check it based on criteria.
                // If no criteria exists, then do nothing.
                // The first error found, we stop and go to the next
                // data element.
            {
                if ( array_key_exists (_GPC_MIN_VAL_, $data)
		     && $value < $data[_GPC_MIN_VAL_] )
                    // Check minimum value boundary.
                {
                    $result = FALSE;
                    $err .= '<strong>"' . $data[_GPC_NAME_] . '"</strong>' . " is too small.<br>";
                    continue 2;
                }

                if ( array_key_exists (_GPC_MAX_VAL_, $data)
		     && $value > $data[_GPC_MAX_VAL_] )
                    // Check maximum value boundary.
                {
                    $result = FALSE;
                    $err .= '<strong>"' . $data[_GPC_NAME_] . '"</strong>' . " is too large.<br>";
                    continue 2;
                }

                if ( array_key_exists (_GPC_MIN_LEN_, $data)
		     && strlen ($value) < $data[_GPC_MIN_LEN_] )
                    // Check minimum length boundary.
                {
                    $result = FALSE;
                    $err .= '<strong>"' . $data[_GPC_NAME_] . '"</strong>' . " is too short.<br>";
                    continue 2;
                }

                if ( array_key_exists (_GPC_MAX_LEN_, $data)
		     && strlen ($value) > $data[_GPC_MAX_LEN_] )
                    // Check maximum length boundary.
                {
                    $result = FALSE;
                    $err .= '<strong>"' . $data[_GPC_NAME_] . '"</strong>' . " is too long.<br>";
                    continue 2;
                }

                if ( array_key_exists (_GPC_PATTERN_, $data) )
                    // Check data pattern.
                {
                    foreach ( $data[_GPC_PATTERN_] as $pattern => $paterr )
                        // Currently all pattern are positive, i.e.
                        // if value matches pattern, it is valid, else invalid,
                        // no other choice.
                    {
                        if ( !preg_match ($pattern, $value) )
                        {
                            $result = FALSE;
                            $err .= '<strong>"' . $data[_GPC_NAME_] . '"</strong>' . $paterr . "<br>";

// Comment out this statement if you want to show all pattern mis-match
// error message, rather than only one.
                            continue 3;
                        }
                    }
                } // END if ( array_key_exists (_GPC_PATTERN_, $data) )
            } // END if ( $data[_GPC_CHECK_TYPE_] == _CHECK_EMPTY_VAL_ ... )
        } // END foreach ( $data[_GPC_VALUE_] as $value )
    } // END foreach ( $mixed as $var => $data )

    return $result;
}

//==========================================================
// Check if $_SERVER["REMOTE_ADDR"] contains a substring defined
// in this file.
// If request is not from the correct IP, then return FALSE.
// Else return TRUE.
function _ValidIP_ ($ipRange)
// $ipRange is the constant defined above for IP ranges.
{
    global $_unlvlib_ip_range_;

    $range = $_unlvlib_ip_range_[$ipRange];

    if ( ! is_array ($range) )
        $range = array ($range);

    foreach ( $range as $ips )
    {
        if ( preg_match("/^$ips/", $_SERVER["REMOTE_ADDR"]) )
            return TRUE;
    }

    return FALSE;
}

//================================================================
function
_ReplaceHTMLMetaTags_ ( &$string )
// Replace all html meta tags for $string, as defined above.
{
/*
    global $_HTML_META_TAGS_;

    foreach ( $_HTML_META_TAGS_ as $pattern => $replace )
        $string = preg_replace ($pattern, $replace, $string);
*/

    global $_HTML_META_TAGS_PAT_, $_HTML_META_TAGS_REPLACE_;

    ksort ($_HTML_META_TAGS_PAT_);
    ksort ($_HTML_META_TAGS_REPLACE_);

    $string = preg_replace ($_HTML_META_TAGS_PAT_, $_HTML_META_TAGS_REPLACE_,
                            $string);
}

//================================================================
function
StrSpaceTrans (&$string,    // The string to be transformed.
                $signal,    // Encode or decode.
                $char       // The character to replace.
              )
// If $signal == ENCODE, replace all spaces in $string with $char.
// If $signal == DECODE, replace all $char in $string with space.
// If $signal is any other signal, return the original string.
// Return the transformed string.
{
    if ( $string == "" )
        return "";

    if ( $signal == ENCODE )
        return preg_replace ("/ /", "$char", $string);
    else if ( $signal == DECODE )
    {
        $char = preg_quote ($char);
        return preg_replace ("/$char/", " ", $string);
    }
    else
        return $string;
}


// ADDITION: 20150828, to fix MS Word smart quotes in database entries.
// Since PHP 5.4.0 and later's htmlentities() is using default encoding, which will silently discard UTF-8 string
// that contains MS Word smart quotes, must call this function before htmlentities().
//=================================================================
function _ConvertSmartQuotes_ ($string)
{
        // 145/146 are single quotes; 147/148 are double quots; 151 is dash.
    $search = array (chr(145), chr(146), chr(147), chr(148), chr(151));
    $replace = array ("'", "'", '"', '"', '-');
    return str_replace ($search, $replace, $string);
}


//===============================================================
function
_EscapeRecordHtml_ref_ (&$record)
// Escape every gpc value in $record for html output, by reference.
// NOTE: All keys are NOT escaped.
// NOTE: Original data in $record are to be changed.
// $record may have two levels of array struct.
{
    if ( is_string ($record) )
    {
        $tmp =  _ConvertSmartQuotes_ ($record);
        $record =  htmlentities ($tmp, _PHP_QUOTE_STYLE_, _PHP_ENCODING_);
        return;
    }

        // Escape $record.
    foreach ( $record as $rkey => $arr_rval )
    {
        if ( ! is_array ($arr_rval[_GPC_VALUE_]) )
        {
            if ( '' != $arr_rval[_GPC_VALUE_] )
            {
                $arr_rval[_GPC_VALUE_] = _ConvertSmartQuotes_ ($arr_rval[_GPC_VALUE_]);
                $record["$rkey"][_GPC_VALUE_] = htmlentities ($arr_rval[_GPC_VALUE_], _PHP_QUOTE_STYLE_, _PHP_ENCODING_);
            }
        }
        else if ( count ($arr_rval[_GPC_VALUE_]) > 0 )
        {
            foreach ( $arr_rval[_GPC_VALUE_] as $akey => $aval )
                    // $akey is natural key.
            {
                $aval = _ConvertSmartQuotes_ ($aval);
                $record["$rkey"][_GPC_VALUE_]["$akey"] = htmlentities ($aval, _PHP_QUOTE_STYLE_, _PHP_ENCODING_);
            }
        }
    }
}


//===============================================================
function
_EscapeRecordHtml_val_ (&$record)
// Escape every gpc value in $record for html output, return a new data struct.
// NOTE: All keys are NOT escaped.
// NOTE: Original data in $record are NOT changed.
// $record may have up to two levels of array struct.
{
    if ( is_string ($record) )
    {
        $return =  _ConvertSmartQuotes_ ($record);
        return htmlentities ($return, _PHP_QUOTE_STYLE_, _PHP_ENCODING_);
    }


    $return = array ();

    foreach ( $record as $rkey => $arr_rval )
    {
        if ( ! is_array ($arr_rval[_GPC_VALUE_]) )
        {
            if ( '' != $arr_rval[_GPC_VALUE_] )
            {
                $arr_rval[_GPC_VALUE_] = _ConvertSmartQuotes_ ($arr_rval[_GPC_VALUE_]);
                $return["$rkey"][_GPC_VALUE_] = htmlentities ($arr_rval[_GPC_VALUE_], _PHP_QUOTE_STYLE_, _PHP_ENCODING_);
            }
        }
        else if ( count ($arr_rval[_GPC_VALUE_]) > 0 )
        {
            foreach ( $arr_rval[_GPC_VALUE_] as $akey => $aval )
                    // $akey is natural key.
            {
                $aval = _ConvertSmartQuotes_ ($aval);
                $return["$rkey"][_GPC_VALUE_]["$akey"] = htmlentities ($aval, _PHP_QUOTE_STYLE_, _PHP_ENCODING_);
            }
        }
    }

    return $return;
}


?>
