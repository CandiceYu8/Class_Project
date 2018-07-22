<?php 
    $ID = (int)$_GET["id"];
    require("./connect.php");
    $sql = mysqli_query($con, "SELECT * FROM cartoons WHERE ID=$ID");
    $row = mysqli_fetch_array($sql);
    $img_src = "images/cartoons/" . $_GET["id"] . ".jpg";

    $pagesize = 3;
    @$p = $_GET['p']?$_GET['p']:1;
    $offset = ($p-1)*$pagesize;
    $sql2 = mysqli_query($con, "SELECT * FROM comments WHERE CartoonID=$ID ORDER BY Date DESC LIMIT $offset, $pagesize");
?>


<!DOCTYPE HTML>
<!--
	one cartoon and its comments
-->
<html>
	<head>
		<title>Back to childhood</title>
		<!-- <meta charset="utf-8" /> -->
        <meta http-equiv="Content-Type" content="text/html;charset=UTF-8">
		<meta name="viewport" content="width=device-width, initial-scale=1" />
		<link rel="stylesheet" href="assets/css/main.css" />
		<link rel="stylesheet" href="assets/css/content.css" />
		<link rel="stylesheet" href="assets/css/font_size.css" />
		<link rel="stylesheet" href="assets/css/single.css" />
	</head>
	<body>
		<div class="page-wrap">

			<!-- Main -->
				<section id="main">

					<!-- Header -->
						<header id="header">
							<div>Made <span>by Candice</span></div>
						</header>

					<!-- Picture and Introduction -->
                    <section id="pic">
                        <div class="inner">
                            <header>
                                <h1>Introduction</h1>
                            </header>
                            <section class="columns double">
                                <div class="column">
                                    <span class="image left special">
                                        <?php echo "<img src=$img_src></img>"; ?>
                                    </span>
                                    <h3>
                                        <?php echo $row['Name']; ?>
                                    </h3>
                                    <p>
                                        <?php echo $row['Introduction']; ?>                                   
                                    </p>
                                    <p>
                                        <a href="cartoons.html"><button class="button" style="position:fixed; right:10px;">返回</button></a>
                                    </p>
                                </div>                                
                            </section>                           
                        </div>     
                    </section>

                    <!-- Comments -->
                    <section id="contact">
                            <div class="inner">
                                <header>
                                    <h1>Comments</h1>
                                </header>
                                <p3>
                                    <?php
                                        while($comments = mysqli_fetch_array($sql2))
                                        { 
                                            if(strlen($comments["Name"])==0)
                                                echo "Name: 匿名" . "<br/>";
                                            else
                                                echo "Name: " . $comments["Name"] . "<br/>"; 
                                            echo "Date: " . $comments["Date"] . "<br/>";
                                            $content = "Comments: " . $comments["Comment"];
                                            echo  wordwrap($content, 50, "<br/>", false) . "<br/>";
                                            echo "<hr/>";
                                        }

                                        $count_result = mysqli_query($con,"select count(*) as count from comments WHERE CartoonID=$ID");  
                                        $count_array = mysqli_fetch_array($count_result);

                                        $pagenum = ceil($count_array['count']/$pagesize);
                                        if($count_array['count']==0)
                                            echo "暂无留言";
                                        else  
                                            echo '共',$count_array['count'],'条留言';

                                        if($pagenum>1){  
                                            for($i = 1; $i<=$pagenum; $i++){  
                                                if($i == $p){  
                                                    echo '[',$i,']';  
                                                      
                                                }else{  
                                                    echo  ' <a href="single.php?id=',$ID,'&p=',$i,'">',$i,'</a>';  
                                                }  
                                            }  
                                        }  
                                    ?>
                                </p3>
                            </div>
                        
                    
                        <div class="column">
                            <form action="submit.php" method="post">
                                <input type="hidden" name="ID" value="<?php echo $ID; ?>">
                                <div class="field half first">
                                    <label for="name">Name</label>
                                    <input name="name" id="name" type="text" placeholder="Name">
                                </div>
                                <div class="field half">
                                    <label for="email">Email</label>
                                    <input name="email" id="email" type="email" placeholder="Email">
                                </div>
                                <div class="field">
                                    <label for="comment">Comment</label>
                                    <textarea name="comment" id="comment" rows="6" placeholder="Comment"></textarea>
                                </div>
                                <ul class="actions">
                                    <li><input value="Send Comments" class="button" type="submit"></li>
                                </ul>
                            </form>
                        </div>
                    </section>
				</section>
		</div>
        
	</body>
</html>