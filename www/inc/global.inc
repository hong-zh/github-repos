<?php

/* Github repos information project.
 * The most starred github repos.
 * Developer: Hong Zhang
 * $Id: global.inc, v 1.0, 2022 $
 */


require_once ('def.inc');



/************************** Start addition on VER 1.5 ***********************/
/************************** Start addition on VER 1.5 ***********************/



    //______________________________________________________________
    // Defining global data structures.
    //______________________________________________________________

$gh_global = array (

        // re-define table name here, easier to call this var than constant.
    "TAB_GH_REPOS_INFO"   => "gh_repos_info",

        // Data struct for items.
    GH_TAG_REPOS => array (
            COL_ID, COL_REPO_ID, COL_NAME, COL_URL, COL_DATE_CREATED, COL_DATE_LAST_PUSH, COL_DESCRIPTION, COL_STARS
    ),

    NEXT_PAGE => '',

    GH_TOTAL_REPOS => 0,
);
    //______________________________________________________________
    // End of $gh_global.
    //______________________________________________________________


    // Global function.



//===============================================================
function
PrintNavLinks ($link, $total, $nextpage)
{
    if ( $total <= GH_RESULTS_PER_PAGE )
        return;

    $totalPages = (int) ($total / GH_RESULTS_PER_PAGE);
    if ( 0 != $total % GH_RESULTS_PER_PAGE )
        $totalPages++;

    $currPage = (int) (($nextpage+1) / GH_RESULTS_PER_PAGE);
    if ( 0 != ($nextpage+1) % GH_RESULTS_PER_PAGE )
        $currPage++;

    echo "<b><i>Total $total records. ", GH_RESULTS_PER_PAGE, " records per page. Page # $currPage / $totalPages.</i></b><br />";

    PrintPrevNextLinks ($link, $nextpage, $total);
    echo "<br />\n";
}

//===============================================================
function
PrintPrevNextLinks ($link, $nextpage, $sizeTab = 0)
// $nextpage starts from zero.
{
$total = 0;

    if ( $nextpage - GH_RESULTS_PER_PAGE * MAX_LINK_PER_SIDE > 0 ) {
        // To the very first page.
        $plink = $link . NEXT_PAGE . "=0";
        echo " <a href=\"$plink\" class=\"pagelink\">|<<</a> \n";

        // Move MAX_LINK_PER_SIDE+1 links back.
        $prevpage = $nextpage - GH_RESULTS_PER_PAGE * (MAX_LINK_PER_SIDE+1);
        if ( $prevpage > 0 ) {
            $plink = $link . NEXT_PAGE . "=$prevpage";
            echo " <a href=\"$plink\" class=\"pagelink\"><<</a> \n";
        }
    }

    // Print the middle page links.
        // The first numbered link.
    $firstpage = $nextpage - GH_RESULTS_PER_PAGE * MAX_LINK_PER_SIDE;
    if ( $firstpage < 0 )
        $firstpage = 0;

        // The last numbered link.
    $lastpage = $nextpage + GH_RESULTS_PER_PAGE * MAX_LINK_PER_SIDE;
    if ( $lastpage >= $sizeTab )
        $lastpage = (int)($sizeTab / GH_RESULTS_PER_PAGE) * GH_RESULTS_PER_PAGE;

    $pageno = (int)($firstpage / GH_RESULTS_PER_PAGE) + 1;
    for ( $i = $firstpage; $i <= $lastpage; $i += GH_RESULTS_PER_PAGE )
    {
        if ( $i != $nextpage ) {
            $plink = $link . NEXT_PAGE . "=$i";
            echo " <a href=\"$plink\" class=\"pagelink\">$pageno</a> \n";
        }
        else
            echo " <span class=\"pagenolink\">$pageno</span> \n";

        $total += GH_RESULTS_PER_PAGE;
        $pageno++;
    }

    if ( $nextpage + GH_RESULTS_PER_PAGE * MAX_LINK_PER_SIDE < $sizeTab ) {
        // Move MAX_LINK_PER_SIDE+1 links forward.
        $page = $nextpage + GH_RESULTS_PER_PAGE * (MAX_LINK_PER_SIDE+1);
        if ( $page < $sizeTab ) {
            $plink = $link . NEXT_PAGE . "=$page";
            echo " <a href=\"$plink\" class=\"pagelink\">>></a> \n";
        }

        // To the very last page.
        $lastpage = (int)($sizeTab / GH_RESULTS_PER_PAGE) * GH_RESULTS_PER_PAGE;
        $plink = $link . NEXT_PAGE . "=$lastpage";
        echo " <a href=\"$plink\" class=\"pagelink\">>>|</a> \n";
    }

    echo "<br />\n";
}

?>
