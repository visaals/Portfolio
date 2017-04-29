<!--Page for user to create account-->
<!DOCTYPE html>
<html>
<head>
    <title>Create an account</title>
    <link rel="stylesheet" type="text/css" href="custom.css">
</head>
<body>
  <?php
  //$_SESSION['token'] = bin2hex(openssl_random_pseudo_bytes(32));

      //display failure alert if necessary based on query string
      if (isset($_GET['failed'])) {
          switch ($_GET['failed']) {
              case "nomatch":
                  echo "Passwords do not match.";
                  break;
              case "passlength":
                  echo "Password must be 6 characters or more in length.";
                  break;
              case "usernametaken":
                  echo "Username already taken. Please try another.";
                  break;
              default:
                  echo 'Unknown error, please try again.';
                  break;
          }
      }
  ?>
    <h2>Create an account below:</h2>
    <form method="POST" action="accountcreator.php">
        <label for="desiredusername">Desired username:</label>
        <input type="text" name="user" id="desiredusername" /> <br><br>
        <label for="desiredpass">Desired password:</label>
        <input type="password" name="pass" id="desiredpass" /><br><br>
        <label for="verifypassinput">Repeat Desired password:</label>
        <input type="password" name="passver" id="verifypassinput" /><br><br>
        <input type="hidden" name="token" value="<?php echo $_SESSION['token'];?>" />
        <input type="submit" value="Create Account" />
    </form>
    <h2>

    </h2>
</body>
</html>
