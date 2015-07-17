<?php

    // configuration
  
    require("../includes/config.php");
    
    if(isset($_SESSION["id"]))
    {
        // Query users cash
        $rows = query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
        $cash = money_format("$%i", $rows[0]["cash"]);
        
        // get users portfolio
        $rows = query("SELECT * FROM portfolio WHERE id = ?", $_SESSION["id"]);
        if(count($rows) > 0)
        {
            // construct the view
            $positions = [];
            foreach($rows as $row)
            {
                $stock = lookup($row["symbol"]);
                if ($stock !== false)
                {
                    $positions[] = [
                        "symbol" => $row["symbol"],
                        "name" => $stock["name"],
                        "shares" => $row["shares"],
                        "price" => money_format("$%i", $stock["price"]),
                        "total" => money_format("$%i", $stock["price"] * $row["shares"])
                    ];
                }
            } 
            // render portfolio
            render("portfolio.php", ["positions" => $positions, "title" => "Portfolio", "cash" => $cash]);
        }
        else
        {
            render("portfolio.php", ["title" => "Portfolio", "cash" => $cash]);
        }
    }
                                                                        
?>
