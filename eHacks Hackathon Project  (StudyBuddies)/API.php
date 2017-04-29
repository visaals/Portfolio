<?php
class RedeemAPI
{
    private $db;

    // constructor to open DB connection
    public function __construct()
    {
        //this is an instance variable
        $this->db = new mysqli('localhost', 'php', '330', 'ehacks');

        if ($this->db->connect_errno) {
            return "Connection Failed: Error: " . $this->db->connect_error;
        } else {
            $this->db->autocommit(false);
            return "Connection Succeeded. ";
        }
    }

    public function __destruct()
    {
        $this->db->close();
    }


    public function redeem_buildings()
    {
        $stmt = $this->db->prepare("SELECT name, lat, lng FROM locations");
        if (!$stmt) {
            echo json_encode(array(
            "success" => false,
            "error" => $this->db->error
        ));
            exit;
        }
    // Bind the parameters
    $stmt->execute();

        $dep_result = $stmt->get_result();
    //putting all deparements into $row array
    while ($row = $dep_result->fetch_assoc()) {
        $rows[] = $row;
    }
        $stmt->close();

        $events_array = array("events" => $rows);
        echo json_encode(
            array_merge(
                array(
            "success" => true,
          //  "display_category" => $display_category
        ), $events_array));
    }

    public function redeem_departments()
    {

      // school_code
      // dept_id
      // dept_name
        $stmt = $this->db->prepare("SELECT school_code, dept_id, dept_name FROM departments");
        if (!$stmt) {
            echo json_encode(array(
              "success" => false,
              "error" => $this->db->error
          ));
            exit;
        }
      // Bind the parameters
      $stmt->execute();

        $dep_result = $stmt->get_result();
      //putting all deparements into $row array
      while ($row = $dep_result->fetch_assoc()) {
          $rows[] = $row;
      }
        $stmt->close();

        $events_array = array("events" => $rows);
        echo json_encode(
              array_merge(
                  array(
              "success" => true,
            //  "display_category" => $display_category
          ), $events_array));
    }

    // Main method to redeem a code
    public function redeem_courses()
    {
        //just send dept names and id
        //select courses from courses wehre deptid = deptid
        //
        $stmt = $this->db->prepare("SELECT * FROM courses");
        if (!$stmt) {
            echo json_encode(array(
            "success" => false,
            "error" => $this->db->error
        ));
            exit;
        }
    // Bind the parameters
    $stmt->execute();

        $dep_result = $stmt->get_result();
    //putting all deparements into $row array
    while ($row = $dep_result->fetch_assoc()) {
        $rows[] = $row;
    }
        $stmt->close();

        $events_array = array("events" => $rows);
        echo json_encode(
            array_merge(
                array(
            "success" => true,
          //  "display_category" => $display_category
        ), $events_array));
    }

    public function query_courses_by_dept($school_code, $dept_id)
    {
        //select name, course code, dept_id from courses where school code and dept id match
        $stmt = $this->db->prepare("SELECT name, course_code, dept_id FROM courses
                      WHERE (dept_id, school_code) = (?,?)
        ");

        if (!$stmt) {
            echo json_encode(array(
            "success" => false,
            "error" => $this->db->error
            ));

            exit();
        }
        $stmt->bind_param('is', $dept_id, $school_code);

        // Bind the parameters
        $stmt->execute();

        $dep_result = $stmt->get_result();

        //putting all deparements into $row array
        while ($row = $dep_result->fetch_assoc()) {
            $rows[] = $row;
        }
        $stmt->close();





        $events_array = array("events" => $rows);
        echo json_encode(
              array_merge(
                  array(
              "success" => true,
            //  "display_category" => $display_category
          ), $events_array));
    }

    public function query_assignment_by_id($assignment_id)
    {
        //select name, course code, dept_id from courses where school code and dept id match
        $stmt = $this->db->prepare("SELECT description,lat,lng FROM assignments
                      WHERE (assignment_id) = (?)
        ");

        if (!$stmt) {
            echo json_encode(array(
            "success" => false,
            "error" => $this->db->error
            ));

            exit();
        }
        $stmt->bind_param('i', $assignment_id);

        // Bind the parameters
        $stmt->execute();

        $dep_result = $stmt->get_result();

        //putting all deparements into $row array
        while ($row = $dep_result->fetch_assoc()) {
            $rows[] = $row;
        }

        $stmt->close();
        // printf($rows[0]["lat"]);
        // printf($rows[0]["lng"]);

        //need to return a location
        $stmt2 = $this->db->prepare("SELECT name FROM locations
                      WHERE (lat, lng) = (?,?)
        ");

        if (!$stmt2) {
            echo json_encode(array(
            "success" => false,
            "error" => $this->db->error,
            "msg"=>"statement 2 is not working"
            ));
            exit();
        }
        // echo $rows[0]["lat"]; 38.643693
        // echo $rows[0]["lng"]; -90.262331

        $stmt2->bind_param('dd', $rows[0]["lat"], $rows[0]["lng"]);
        $stmt2->execute();

        $stmt2->bind_result($location_name);
        while ($stmt2->fetch()) {
            //printf($location_name);
        }

        $stmt2->close();

        echo json_encode(array(
              "success" => true,
              "location_name" => $location_name,
              "desc"=> $rows[0]["description"]
            //  "display_category" => $display_category
          ));
    }

    public function query_users_by_assignment($assignment_id)
    {
        //select name, course code, dept_id from courses where school code and dept id match
        $stmt = $this->db->prepare("SELECT username FROM users
                      WHERE (current_assignment_id) = (?)
        ");

        if (!$stmt) {
            echo json_encode(array(
            "success" => false,
            "error" => $this->db->error
            ));

            exit();
        }
        $stmt->bind_param('i', $assignment_id);

        // Bind the parameters
        $stmt->execute();

        $dep_result = $stmt->get_result();

        //putting all deparements into $row array
        while ($row = $dep_result->fetch_assoc()) {
            $rows[] = $row;
        }

        $stmt->close();
        // printf($rows[0]["lat"]);
        // printf($rows[0]["lng"]);

        echo json_encode(array(
              "success" => true,
              "list_of_people" => $rows,

            //  "display_category" => $display_category
          ));
    }










    public function query_assignments_by_course($school_code, $dept_id, $course_code)
    {
        //select name, course code, dept_id from courses where school code and dept id match
        $stmt = $this->db->prepare("SELECT name, assignment_id FROM assignments
                      WHERE (dept_id, school_code, course_code) = (?,?,?)
        ");
        $stmt->bind_param('iss', $dept_id, $school_code, $course_code);

        if (!$stmt) {
            echo json_encode(array(
            "success" => false,
            "error" => $this->db->error
            ));

            exit();
        }
        // Bind the parameters
        $stmt->execute();

        $dep_result = $stmt->get_result();

        //putting all deparements into $row array
        while ($row = $dep_result->fetch_assoc()) {
            $rows[] = $row;
        }
        $stmt->close();

        $events_array = array("events" => $rows);
        echo json_encode(
              array_merge(
                  array(
              "success" => true,
            //  "display_category" => $display_category
          ), $events_array));
    }


    //create assignment by user
    public function create_assignment($title, $school_code, $dept_id, $course_code, $user_id, $lat, $lng, $description)
    {

        //begin statement
        $stmt = $this->db->prepare("INSERT INTO assignments (name, school_code, dept_id, course_code, user_id, lat, lng, description) values (?,?,?,?,?,?,?,?)");
        if (!$stmt) {
            printf("Query Prep Failed: %s\n", $mysqli->error);
            exit();
        }

        $stmt->bind_param('ssisidds', $title, $school_code, $dept_id, $course_code, $user_id, $lat, $lng, $description);

        if (!$stmt) {
            printf("Query Prep Failed: %s\n", $mysqli->error);
            exit();
        }
        printf("%s\n", $this->db->error);
        $stmt->execute();
        var_dump($stmt);
        if ($stmt->affected_rows < 1) {
            echo json_encode(array(
                "success" => false,
                "error" => "Could not remove assignment"
            ));
            exit;
        }

        $stmt->close();

        //echo depending on whether assignment was added
        // if ($success) {
            echo json_encode(array(
                "success" => true,
                "error" => "none",
                "msg" => "Sucessfully added assignment."
            ));
        exit();
        // } else {
        //     echo json_encode(array(
        //         "success" => false,
        //         "error" => "Add failed",
        //         "msg" => "Could not add!"
        //   ));
        //     exit();
        // }
    }


    //add user to ongoing assignment
    public function add_user_to_assignment()
    {
        //$user = $_SESSION['user'];
        $user = $_POST['user'];
        $assignment_id = $_POST['assignment_id'];

        $stmt = $this->db->prepare('update users set current_assignment_id = ? where username = ?');
        if (!$stmt) {
            printf("Query Prep Failed: %s\n", $mysqli->error);
            exit;
        }
        $stmt->bind_param('i', $assignment_id, $user);
        $stmt->execute();

                //echo based on result
        if ($stmt->affected_rows < 1) {
            echo json_encode(array(
                "success" => false,
                "error" => "Could not remove assignment"
            ));
            exit;
        }
        $stmt->close();
        echo json_encode(array(
              "success" => true,
              "error" => "none"
              ));
    }


    //delete user from ongoing assignment
    public function delete_user_from_assignment()
    {
        $user = $_SESSION['user'];
        $assignment_id = $_POST['assignment_id'];
    }


    //delete assignment
    public function delete_assignment()
    {
        $assignment_id = $_POST['assignment_id'];
        $stmt = $this->db->prepare('delete from assignments where assignment_id=?');
        if (!$stmt) {
            printf("Query Prep Failed: %s\n", $mysqli->error);
            exit;
        }
        $stmt->bind_param('i', $assignment_id);
        $stmt->execute();

        //echo based on result
        if ($stmt->affected_rows < 1) {
            echo json_encode(array(
                "success" => false,
                "error" => "Could not remove assignment"
            ));
            exit;
        }
        $stmt->close();
        echo json_encode(array(
              "success" => true,
              "error" => "none"
              ));
    }

    // get locations


    // find closest study location





//end of class bracket
}

//querying assignments by location
//querying assignments by department or courses

// adding users to assignments
// create or delete assigments



$api = new RedeemAPI;
$api->__construct();
