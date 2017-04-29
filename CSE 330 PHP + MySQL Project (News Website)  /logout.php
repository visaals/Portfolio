
<?php

      session_start();
      header("Content-Type: application/x-www-form-urlencoded");

      session_destroy();
      printf("logged out succeeded");
      header("Location: index.html");
      exit;
?>
