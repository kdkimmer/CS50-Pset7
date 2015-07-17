<?php

    // configuration
    require("../includes/config.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate the name
        if (empty($_POST["symbol"]))
        {
            apologize("Please enter the stock symbol.");
        }
        
        // Query Yahoo
        {
            $stock = lookup($_POST["symbol"]);
        }
        // Check if we returned nothing
        if ($stock === false)
        {
            apologize("The stock symbol was invalid.");
        }
        else
        {
            // render the result form
            render("quote_price.php", ["title" => "Quote", "symbol" => $stock["symbol"], "name" => $stock["name"], "price" => $stock["price"]]);
        }
    }
    else
    {
        // else render form
        render("quote_form.php", ["title" => "Quote"]);
    }
?>

