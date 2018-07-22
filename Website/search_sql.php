<?php
    if(empty($_POST["search"]))
        echo "<script type='text/javascript'>
              alert('请输入内容');
              history.back();
              </script>";
    else{
        $search = addslashes(htmlspecialchars(trim($_POST['search'])));
        require("./connect.php");
        $sql = mysqli_query($con, "SELECT * FROM cartoons WHERE Name like '%$search%'");
        if($row = mysqli_fetch_array($sql)){
            $loc = "Location:single.php?id=" . $row["ID"];
            header($loc);
        }
        else{
            // header("Location:no_result.html");
            $baidu_search = "https://www.baidu.com/s?ie=utf-8&f=8&rsv_bp=1&rsv_idx=1&tn=baidu&wd=".$search;
            ?>
            <!DOCTYPE html>
            <html>
                <head>
                    <title>No result</title>
                    <meta charset="utf-8" />
                    <meta name="viewport" content="width=device-width, initial-scale=1" />
                    <link rel="stylesheet" href="assets/css/no_result.css" />
                </head>

                <body>
                    <h1>No result </h1>
                    <h2> 
                        <a href="search.php"> Go back!</a> 
                    </h2>
                    <h3>
                        <a href= <?php echo $baidu_search?> target="_blank">Or click here to search.</a>
                    </h3>
                </body>

            </html>
            <?php
        }
    }

?>