<?php

/* Github Repo script.
 * The most starred github repos.
 * Pull repo information from local database, present to web interface.
 * Developer: Hong Zhang
 * $Id: gh.inc, v 1.0 $
*/


/*
include("env.inc");
include("dblinks/pat_newbk.inc");
include("admin/gh_global.inc");
*/



gh_get_post_data ();


gh_find_total_repos ();

// Main script flow.
gh_show_all_repos ();


//================================================================
function gh_get_post_data ()
// Get form POST data and set up global storage.
{
    global $gh_global;


        // The next page # to extract.
    $gh_global[NEXT_PAGE] = _GetGPCData_ (NEXT_PAGE);
    if ( ! is_numeric ($gh_global[NEXT_PAGE]) && $gh_global[NEXT_PAGE] < 1 )
        $gh_global[NEXT_PAGE] = 0;
}


//================================================================
function
gh_show_all_repos ()
// Display all repos, paginated.
{
    global $gh_global, $_phpself_;

        // Extract starting from this page.
    $nextpage = $gh_global[NEXT_PAGE];

        // $results is the sql results set handle. 
    gh_connect_repos_table ($results, $nextpage );


    // Print numerical navigational links, if splitting pages.
    $link = "$_phpself_?";
    $totalcount = $gh_global[GH_TOTAL_REPOS];

    PrintNavLinks ($link, $totalcount, $nextpage);


    if ( mysqli_num_rows ($results) <= 0 )
        echo "<div style='color:brown;font-weight:bold;'>End of repo listing.</div><BR>\n";

    echo "<hr />\n";


    echo "<div class='clear-fix'>\n";
    echo "<div class='item-list'>\n";
    echo "<ul class='repo-list'>\n";
    while ( $repo = mysqli_fetch_assoc ($results) )
    {
        echo "<li class='repo-rec'>\n";

           gh_print_repo_info ($repo);

        echo "</li>\n";
    }
    echo "</ul>\n";
    echo "<div class='clear-fix'></div>\n";
    echo "</div>\n";
    echo "</div>\n";

    echo "<div class='clear-fix'>\n";
    echo "<div id='end-item-list'>\n";
    // Print numerical navigational links, if splitting pages.

    PrintNavLinks ($link, $totalcount, $nextpage);
//    echo "END OF LISTING.<br /><hr />\n";

    echo "<hr />\n";

    echo "</div>\n";
    echo "</div>\n";


    echo "<div class='clear-fix'></div>\n";
}



//=================================================================
function gh_print_repo_info (&$repo)
{
    global $gh_global;


    $id = $repo[COL_ID];

    $repo_id = $repo[COL_REPO_ID];
    $name = $repo[COL_NAME];
    $url = $repo[COL_URL];
    $data_created = $repo[COL_DATE_CREATED];
    $data_last_push = $repo[COL_DATE_LAST_PUSH];
    $desc = $repo[COL_DESCRIPTION];
    $stars = $repo[COL_STARS];

echo "<div class='clear-fix'>\n";
    echo "<div class='repo-github'>\n";

    echo "<div class='repo-detail'>\n";

    echo "<dl>\n";

    if ( '' != $url )
        echo "<a href=\"$url\">", $name, "</a> \n";


    gh_print_repo_details ($repo);

    echo "</dl>\n";

}


//===============================================================
function gh_print_repo_details (&$repo)
// Print all repo details.
{
    echo "<span>";
    $anchor = '';
        $id_web = htmlentities ($repo[COL_ID], ENT_QUOTES);

        $repo_id = htmlentities ($repo[COL_REPO_ID]);
        $date_created = htmlentities ($repo[COL_DATE_CREATED]);
        $date_last_push = htmlentities ($repo[COL_DATE_LAST_PUSH]);
        $desc = htmlentities ($repo[COL_DESCRIPTION]);
        $stars = htmlentities ($repo[COL_STARS]);

        $info = "Repo ID: " . $repo_id . "<BR>\n";
        $info .= "Date Created at: " . $date_created . "<BR>\n";
        $info .= "Date Last Pushed at: " . $date_last_push . "<BR>\n";
        $info .= "Description: " . $desc . "<BR>\n";
        $info .= "Stars: " . $stars . "<BR>\n";

        echo '<span class="trigger" onClick="showContent(\'repo',
             $id_web, '\');swapIconRec(\'icon', $id_web, '\')" id="icon',
             $id_web, '">[+]</span>';

        echo "<div id=\"repo", $id_web, "\" class=\"repo\">$info</div>";
        echo "</span>\n";

        echo "<BR>\n";
    echo "</span>";
}


//=================================================================
function gh_connect_repos_table (&$results, $nextpage)
// Connect to repos table.
// $nextpage is the start number of record in database, NOT page number.
// $results is the handle returned back to caller for manipulation.
{
    global $db_gh, $gh_global;

    $cols = implode (', ', $gh_global[GH_TAG_REPOS]);

        // When sorting, skip leading article: the, a, an.
    $sql = 'SELECT ' . $cols . ' FROM ' . TAB_GH_REPOS_INFO . " ORDER BY " . COL_STARS . " DESC "
           . " LIMIT $nextpage, " . GH_RESULTS_PER_PAGE;

    $results = mysqli_query ($db_gh, $sql)
        or die("Encountered some database problem2, please come back later. " . mysqli_error ($db_gh));
}


//=================================================================
function gh_find_total_repos ()
// Connect to repos table.
// Find the total # of repos stored in database, store the number in gh_global.
{
    global $db_gh, $gh_global;

        // When sorting, skip leading article: the, a, an.
    $sql = 'SELECT COUNT(' . COL_ID . ') FROM ' . TAB_GH_REPOS_INFO;

    $results = mysqli_query ($db_gh, $sql)
        or die("Encountered some database problem2, please come back later. " . mysqli_error ($db_gh));

    $row = mysqli_fetch_row ($results);
    list ($gh_global[GH_TOTAL_REPOS]) = $row;
}

?>
