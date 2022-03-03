<?php

/*
    This script manages github repo information table.
    Extract github repo information from github site, the most starred repos.
    Parse information of each repo, load into local database.
*/


date_default_timezone_set('America/Los_Angeles');


/*
ini_set('display_startup_errors',1);
ini_set('display_errors',1);
error_reporting(-1);
*/


require_once ("init_vars.inc");

/*
include_once ("../inc/db_test.inc");
include_once ("../inc/def.inc");
//include_once ("libspec_new.inc");
//include_once ("newbkdb_dev.inc");
include_once ("../inc/global.inc");
*/

/*
header("X-Accel-Buffering: no");
header('Content-Type: text/plain');
 */

ob_implicit_flush(1);    // Force immediate printing.


    // For initialized subjects.
$subjects = array ();


    // Some global vars.
$total_repos = 0;

$total_requests = 0;


$start_time = time();   // UNIX timestamp in seconds.

    //______________________________________________________________
    // Main processing flow.
    //______________________________________________________________

//gh_drop_gh_table ();    // Drop existing table, to start freshly.
gh_create_gh_db ();     // To be on safe side, create database anyway if not exist yet.
gh_create_gh_table ();  // Create the repo table.
gh_init_gh_table ();    // Load table with github data.
exit(0);


    //______________________________________________________________
    // End main processing flow.
    //______________________________________________________________


    //______________________________________________________________
    // Function definitions.
    //______________________________________________________________

//==================================================================
function gh_drop_gh_table ()
// Drop github repo table.
{
    global $db_gh, $gh_global;

    echo "Dropping github repo table ......\n";


        // Do this anyway, in case database hasn't been selected yet.
    mysqli_select_db ($db_gh, DB_GH_REPOS);

    // Drop tables, just be a little careful.
    $query = 'DROP TABLE IF EXISTS ' . TAB_GH_REPOS_INFO;
    $result = mysqli_query ($db_gh, $query)
        or die("Failed droping items github repo table: " . mysqli_error ($db_gh));

    echo "Dropped github repo table\n";
}


//==================================================================
function gh_create_gh_db ()
// Create github repo database.
{
    global $db_gh, $gh_global;

    echo "Creating github repo database ......\n";
    $query = 'CREATE DATABASE IF NOT EXISTS ' . DB_GH_REPOS;
    $result = mysqli_query ($db_gh, $query)
        or die("Failed creating github repo database: " . mysqli_error ($db_gh));

    echo "Created github repo database\n";
}


//==================================================================
function gh_create_gh_table()
// Create github repo table.
{
    global $db_gh, $gh_global;

    echo "Creating github repo table ......<br>\n";


// ok.
    // Create table TAB_ITEMS.
    // Column names are alphabetically ordered.
    // Pieces of call number start using VARCHAR(20) in this version,
    // replacing FLOATING/INT, etc. Space should be long enough.
    $query =<<<EOD
CREATE TABLE IF NOT EXISTS $gh_global[TAB_GH_REPOS_INFO] (
    id              INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,

    repo_id         INT UNSIGNED NOT NULL UNIQUE,
    name            VARCHAR(255) NOT NULL,
    url             VARCHAR(1024) NOT NULL,
    date_created    DATETIME DEFAULT NULL,
    date_last_push  DATETIME DEFAULT NULL,
    description     TEXT,
    stars           INT,

    INDEX (repo_id),
    stamp           TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
) ENGINE=InnoDB;
EOD;

    $result = mysqli_query ($db_gh, $query);

if ( ! $result )
{
    echo $query, "<BR>";
    echo mysqli_error ($db_gh), "<BR>";
}
//        or die("Failed creating github repo info table: " . mysqli_error ($db_gh));
    echo "Succeeded creating github repo info table.<BR>\n";
}


//==================================================================
function gh_init_gh_table ()
// Extract repo data from github, load into local github repo table.
{
    echo "Initializing github repo info table ......<BR>\n";

    gh_extract_starred_github_repos ();

    echo "github repo info table has been initialized.<BR>\n\n";
}


//==================================================================
function gh_extract_starred_github_repos ()
// Request repo info from github, up to GH_MAX_RECORDS repos.
{
    global $db_gh, $gh_global, $total_repos, $total_requests;

    echo "Request list of starred repos from github ......<BR>\n";

    if ( DEBUG )
    {
        echo GH_SEARCH_URL_PART1, "\n";
        echo GH_SEARCH_URL_PART2, "\n";
        echo GH_SEARCH_URL_PART3, "\n";
        echo GH_SEARCH_URL_PART4, "\n";
    }

        // Extract up to that many repos from github.
        // Lower star range slowly to get more repos.
    $min = GH_STAR_MAX - GH_STAR_GAP;
    $max = GH_STAR_MAX;

    $search_range = SEARCH_RANGE;
    while ( $total_repos < GH_MAX_RECORDS )
    {
        gh_extract_star_ranges ($min, $max);

        $min -= GH_STAR_GAP;
        $max -= GH_STAR_GAP;

        if ( $min < 0 )
            $min = 0;
        if ( $max <= 0 )
            return;

echo "min: $min\n";
echo "max: $max\n";
echo "total repos: $total_repos<BR>\n";
    }
    // END: while ( $total_repos < GH_MAX_RECORDS )
}


//==================================================================
function gh_extract_star_ranges ($min, $max)
// Request repo info from github, for the star range from $min - $max.
{
    global $db_gh, $gh_global, $total_repos, $total_requests, $start_time;

    $page_start = 1;    // Always start with page 1.
    $page_max = 10;     // Assume this many pages, the first search should update this value.
    $bool_total_updated = FALSE;    // Total repos hasn't been updated so far.

    while ( $page_start <= $page_max )
    {
            // Always search using a star range. Set the constant accordingly.
        if ( SEARCH_RANGE )
            $gh_url = GH_SEARCH_URL_PART1 . GH_SEARCH_URL_PART2 . $min . '..' . $max . GH_SEARCH_URL_PART3 . GH_RESULTS_PER_PAGE . GH_SEARCH_URL_PART4 . $page_start;
        else
            $gh_url = GH_SEARCH_URL_PART1 . GH_SEARCH_URL_PART2 . GH_STAR_MAX . GH_SEARCH_URL_PART3 . GH_RESULTS_PER_PAGE . GH_SEARCH_URL_PART4 . $page_start;

            // Didn't add Auth token into header, since github removed the access token.
            // 
        $gh_header = array (
            CURL_HEAD_ACCEPT, CURL_HEAD_CHARSET
        );

        if ( DEBUG )
            echo 'request url: ', $gh_url, "\n";

        $headers = '';

            // Start requesting repo info from github.
        $ch = curl_init ();
        curl_setopt ($ch, CURLOPT_URL, $gh_url);
        curl_setopt ($ch, CURLOPT_HTTPHEADER, $gh_header);
        curl_setopt ($ch, CURLOPT_HEADER, TRUE);    // Need header for X-RateLimit-Limit, X-RateLimit-Remaining.
        curl_setopt ($ch, CURLOPT_USERAGENT, CURL_USER_AGENT);
        curl_setopt ($ch, CURLOPT_RETURNTRANSFER, 1);

        $gh_data = curl_exec($ch);

            // how big are the headers
        $headerSize = curl_getinfo( $ch , CURLINFO_HEADER_SIZE );
        $headers = substr( $gh_data , 0 , $headerSize );
        $body = substr( $gh_data, $headerSize );

/*
print_r ($headers);
echo "\n";
*/

            // Retrieve header information.
        // Convert the $headers string to an indexed array
        $headers_indexed_arr = explode("\r\n", $headers);

        // Define as array before using in loop
        $headers_arr = array();
        // Remember the status message in a separate variable
        $status_message = array_shift($headers_indexed_arr);

        // Create an associative array containing the response headers
        foreach ($headers_indexed_arr as $value) {
          if(false !== ($matches = explode(':', $value, 2))) {
            $headers_arr["{$matches[0]}"] = trim($matches[1]);
          }                
        }

            // Remaining # of requests for this hour.
            // Depending on calling web interface or CLI, this header tag may or may not be present.
            // So it is not a reliable variable.
	if ( defined ($headers_arr['X-RateLimit-Remaining']) )
	    $limit_remain = $headers_arr['X-RateLimit-Remaining'];

echo "remaining # of requests: ", $limit_remain, "\n";

            // Sleep some time for the next hour.
            // Seems can only make 30 requests per hour, even with access token.
/*
        if ( $limit_remain < 1 )
        {
            $now = time ();
            $sleep = 3600 - ($now - $start_time);


            echo "sleeping ", floor($sleep/60), " minutes ", $sleep %60, " seconds until ", date("F j, Y, g:i a", $start_time + 3600), "\n";
            sleep ($sleep);
        }
 */
/*
print_r ($headers_arr);
echo "\n";
*/

        curl_close($ch);


            // Seems this var is useless.
        $total_requests++;


        $repos = json_decode ($body, TRUE);
/*
        if ( DEBUG )
            print_r ($repos);
*/


        $total_cnt = $repos['total_count'];
//echo "total cnt: ", $total_cnt, "\n";

/*
    [message] => Only the first 1000 search results are available
    [documentation_url] => https://docs.github.com/v3/search/
*/

        if ( $total_cnt < 1 )
        {
print_r ($repos);
echo "\n";
            return;
        }
        else
            $total_repos += count ($repos['items']);     // Update total repos so far.

       if ( ! $bool_total_updated )
       {
//            $total_repos += $total_cnt;     // Update total repos so far.
            $page_max = ceil ($total_cnt / GH_RESULTS_PER_PAGE);  // Round up, this many pages for the star range.
            $bool_total_updated = TRUE;
        }
/*
        else
            $bool_total_updated = TRUE;
*/

        if ( DEBUG )
        {
            echo "total cnt: ",  $total_cnt, "\n";
            echo "total repos: ",  $total_repos, "\n";
        }

//        $page_max = ceil ($total_cnt / GH_RESULTS_PER_PAGE);  // Round up, this many pages for the star range.


        foreach ( $repos['items'] as $item )
        {
            $repo_info = array ();

            $repo_info[COL_REPO_ID] = $item['id'];     // This github id should be unique.
            $repo_info[COL_NAME] = $item['name'];
            $repo_info[COL_URL] = $item['html_url'];
            $repo_info[COL_DATE_CREATED] = $item['created_at'];
            $repo_info[COL_DATE_LAST_PUSH] = $item['pushed_at'];
            $repo_info[COL_DESCRIPTION] = $item['description'];
            $repo_info[COL_STARS] = $item['stargazers_count'];
/*
            if ( DEBUG )
                print_r ($repo_info);
*/

            gh_store_repo_info ($repo_info);
        }

        $page_start++;  // Go to next page.
    }
// while ( $page_start <= $page_max );
    // END: while ( $page_start < $page_max )

    return;
}

//==================================================================
function gh_store_repo_info ($info)
// Store repo info into database. $info is array with elements corresponding to database table columns, except primary key id.
{
    global $db_gh, $gh_global, $total_repos;

    $query = 'INSERT INTO ' . TAB_GH_REPOS_INFO . ' (`' . COL_REPO_ID . '`, `' . COL_NAME . '`, `' . COL_URL . '`, `' . COL_DATE_CREATED
             . '`, `' . COL_DATE_LAST_PUSH . '`, `' . COL_DESCRIPTION . '`, `' . COL_STARS . '`) VALUES(';

/* example dates from github:
                    [created_at] => 2014-12-24T17:49:19Z
                    [updated_at] => 2022-02-28T01:09:23Z
                    [pushed_at] => 2022-02-27T19:31:46Z
*/
        // Update date string, make them suitable for mysql date definition.
    $info[COL_DATE_CREATED] = str_replace ('T', ' ', $info[COL_DATE_CREATED]); 
    $info[COL_DATE_CREATED] = str_replace ('Z', '', $info[COL_DATE_CREATED]); 

    $info[COL_DATE_LAST_PUSH] = str_replace ('T', ' ', $info[COL_DATE_LAST_PUSH]); 
    $info[COL_DATE_LAST_PUSH] = str_replace ('Z', '', $info[COL_DATE_LAST_PUSH]); 


        // Escape special chars.
    $info[COL_NAME] = mysqli_real_escape_string ($db_gh, $info[COL_NAME]); 
    $info[COL_URL] = mysqli_real_escape_string ($db_gh, $info[COL_URL]); 
    $info[COL_DESCRIPTION] = mysqli_real_escape_string ($db_gh, $info[COL_DESCRIPTION]); 

    $query .= "'" . $info[COL_REPO_ID] . "', "
             . "'" . $info[COL_NAME] . "', "
             . "'" . $info[COL_URL] . "', "
             . "'" . $info[COL_DATE_CREATED] . "', "
             . "'" . $info[COL_DATE_LAST_PUSH] . "', "
             . "'" . $info[COL_DESCRIPTION] . "', "
             . "'" . $info[COL_STARS] . "')";

//echo $query, "\n";
    $result = mysqli_query ($db_gh, $query);


    // Keep silent.
/*
    if ( FALSE === $result )
        echo "Failed inserting github repo info: " . mysqli_error ($db_gh);
*/
//    echo "Succeeded storing github repo info. id: ", mysqli_insert_id($db_gh) , "\n";
}


?>
