<?php

/* Define constants, vars to be used across all scripts. */


define('ROOT', dirname(__FILE__));


    /* Define database table column names.
        Some columns are shared by different types of items.
        Some are only used by a particular type of items.
        Types: Electronic (E), Music (M), Physical (P).
    */

define ('DEBUG', TRUE);

define ('SEARCH_RANGE', TRUE);
//define ('SEARCH_RANGE', FALSE);



define ('DB_GH_REPOS', 'gh_repos');                 // database for github repos.

    // Table name.
define ('TAB_GH_REPOS_INFO', 'gh_repos_info');      // Table for github repos.


    // Table column names.
define ('COL_ID', 'id');                            // Table id, primary auto-increment key.
define ('COL_REPO_ID', 'repo_id');                  // Github repo id, should be unique.
define ('COL_NAME', 'name');                        // Github repo name.
define ('COL_URL', 'url');                          // Github repo url.
define ('COL_DATE_CREATED', 'date_created');        // Github repo created date.
define ('COL_DATE_LAST_PUSH', 'date_last_push');    // Github repo last-pushed date.
define ('COL_DESCRIPTION', 'description');          // Github repo description.
define ('COL_STARS', 'stars');                      // Github repo number of stars.


    // Parameters used in curl function call.
define ('CURL_USER_AGENT', 'User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:60.0) Gecko/20100101 Firefox/81.0');

define ('CURL_HEAD_CHARSET', "Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7"); 
define ('CURL_HEAD_ACCEPT', 'Accept: application/vnd.github.v3+json');  // Accept return data in jason format.
define ('CURL_HEAD_AUTH', 'Authorization: token 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');  // My own access token at github.
define ('GH_SEARCH_URL_PART1', 'https://api.github.com/search/repositories');   // 1st part of request url.

// for testing purpose.
//define ('GH_SEARCH_URL_PART2', '?q=' . urlencode ('is:public org:github') . '&' . urlencode ('stars:')); // 2nd part of request url, missing star number at end.


if ( ! SEARCH_RANGE)
//    define ('GH_SEARCH_URL_PART2', '?q=' . urlencode ('is:public') . '&type=Repositories' . '&' . urlencode ('stars:') . '>'); // 2nd part of request url, missing star number at end.
//    define ('GH_SEARCH_URL_PART2', '?q=is:public&type=Repositories&stars:>'); // 2nd part of request url, missing star number at end.
    define ('GH_SEARCH_URL_PART2', '?q=stars:>'); // 2nd part of request url, missing star number at end.
else
//    define ('GH_SEARCH_URL_PART2', '?q=' . urlencode ('is:public') . '&' . urlencode ('stars:')); // 2nd part of request url, missing star number at end.
    define ('GH_SEARCH_URL_PART2', '?q=stars:'); // 2nd part of request url, missing star number at end.

// For debugging purpose.
//define ('GH_SEARCH_URL_PART2', '?q=stars:'); // 2nd part of request url, missing star number at end.


define ('GH_SEARCH_URL_PART3', '&is:public&sort=stars&order=desc&per_page=');   // missing number per page.
define ('GH_SEARCH_URL_PART4', '&page='); // missing page number for result set at end.


define ("NEXT_PAGE", "np");             // Tag for where to start for next page.
define ('GH_RESULTS_PER_PAGE', 100);    // This many records per page from search results.
define ("MAX_LINK_PER_SIDE", 10);       // Display so many links before/after
                                        // the current link on each page.


define ('GH_STAR_GAP', '5000');         // Gap between min/max star range.
define ('GH_STAR_MAX', '40000');        // Maximum star range.

define ('GH_MAX_RECORDS', 5000);    // Extract up to this many repos from github.


define ('GH_MAX_REQUESTS', 30);     // Maximum # of requests per hour to github.


    /* Various tag names. */
define ('GH_TAG_REPOS', 'repos');

define ('GH_TOTAL_REPOS', 'total_repos');   // Total # of repos.

?>

