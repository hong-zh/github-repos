<?php
    //
    // This file defines data for connecting to our database.
    // Modify them to fit the actual database information.
    //

    $server = "database";
    $login = "docker";
    $passwd = "docker";
    $database = "gh_repos";

    // connect to staff info database.
    $db_gh = mysqli_connect($server, $login, $passwd)
          or die("Could not connect: " . mysqli_error($db_gh));
    mysqli_select_db ($db_gh, $database);

/*
$charset = mysqli_character_set_name($db);
printf ("Current character set is %s\n", $charset);
*/

?>
