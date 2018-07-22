<?php
header('Content-type:text/html;charset=utf-8');
$con = mysqli_connect("localhost","root","root");
if (!$con)
{
    die('Could not connect: ' . mysqli_error($con));
}

mysqli_select_db($con, "my_db");
mysqli_query($con,"set names utf8");
?>