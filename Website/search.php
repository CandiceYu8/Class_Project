<!DOCTYPE HTML>
<!--
	search the cartoon you want to write comments
-->
<html>
	<head>
		<title>Back to childhood</title>
		<meta charset="utf-8" />
		<meta name="viewport" content="width=device-width, initial-scale=1" />
		<link rel="stylesheet" href="assets/css/main.css" />
		<link rel="stylesheet" href="assets/css/content.css" />
		<link rel="stylesheet" href="assets/css/font_size.css" />
		<link rel="stylesheet" href="assets/css/search.css" />
	</head>
	<body>
		<div class="page-wrap">

			<!-- Nav -->
				<nav id="nav">
					<ul>
						<li><a href="index.html" class="active"><span class="icon fa-home"></span></a></li>
						<li><a href="cartoons.html"><span class="icon fa-camera-retro"></span></a></li>
						<li><a href="search.php"><span class="icon fa-search"></span></a></li>
					</ul>
                </nav>
                
            <!-- Main -->
				<section id="main">

                    <!-- Header -->
                        <header id="header">
                            <div>Made <span>by Candice</span></div>
                        </header>

                    <!-- Search -->
                        <section id="search">
                            <div class="inner">
								<h1 style="">What are you looking for?</h1>
                                <form action="search_sql.php" method="post">
									<input type="text" name="search" placeholder="Searching..." >
									<button type="submit" style="top:72.3px;"></button>                                    
                                </form>
                            </div>
                        </section>

                </section>
		</div>

		<!-- Scripts -->
			<script src="assets/js/jquery.min.js"></script>
			<script src="assets/js/jquery.poptrox.min.js"></script>
			<script src="assets/js/main.js"></script>

	</body>
</html>