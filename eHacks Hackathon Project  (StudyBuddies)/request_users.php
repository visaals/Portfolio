<?php

require 'API.php';

$assignment_id = $_POST['assignment_id'];


$api->query_users_by_assignment($assignment_id);
