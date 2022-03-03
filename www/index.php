<?php

/*
ini_set('display_startup_errors',1);
ini_set('display_errors',1);
error_reporting(-1);
*/

?>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/strict.dtd">

<HTML>

<head>
<!--Begin title and metadata-->
<title>Github Repo Information</title>

<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<meta name="description" content="Most starred repos from Github.">
<meta name="keywords" content="book, music, e-resource, newly cataloged">


<!--these two tags are used to allow content providers and page editors to pull 
together lists of their own pages using the verity search engine.  "author" is 
the content provider,  "editor" is the page editor-->
<meta name="author" content="Zhang, Hong">
<meta name="editor" content="Zhang, Hong">
<!--End title and metadata-->


<script type="text/javascript" language="JavaScript" src="inc/gh.js">

</script>

<style>
@import url("inc/gh.css");
</style>

</head>


<body lang="en" leftmargin="0" topmargin="0" marginwidth="0" marginheight="0">

<!--include virtual src=""-->
<!-- include virtual="./topbar.html" -->


<?php
    // These are moved here from newbk.inc, since we need to upgrade breadcrumb

@readfile ("topbar.html");
include_once ("init_vars.inc");

?>
<!--end top menu bar-->
    

	  <div ID="contentarea">
	<div ID="breadcrumbs">
	<a href="./gh_db_init.php">Reload the most starred Github Repos</a>


	</div>
	
	<!--Begin page content-->
        <p> 
        <H2>The most starred public GitHub Repos</H2>






<!-- include php script for displaying staff info -->
<?php

include("./gh.inc");

?>
<!-- END include php script for displaying staff info -->

	
	<!--end page content-->

</body>
</html>
