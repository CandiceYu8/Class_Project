<?php
    // 表单信息处理
    $Name = addslashes(htmlspecialchars(trim($_POST['name'])));
    $Email = addslashes(htmlspecialchars(trim($_POST['email'])));
    $Comment = addslashes(htmlspecialchars(trim($_POST['comment'])));

    // $Name = $_POST['name'];
    // $Email = $_POST['email'];
    // $Comment = $_POST['comment'];
    
    // 数据写入库表
    require("./connect.php");
    $ID = (int)$_POST["ID"];
    $insert_sql = "INSERT INTO comments(CartoonID, Name, Email, Comment, Date)
                                VALUES('$ID', '$Name', '$Email', '$Comment', now())";

    if(mysqli_query($con, $insert_sql)){
        $loc = "Location:single.php?id=" . $ID;
        header($loc);
    }
    else{
        die('Error: ' . mysqli_error($con));
    }
?>     
