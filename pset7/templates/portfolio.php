
    <a href="quote.php">Quote</a>
    <a href="buy.php">Buy</a>
    <a href="sell.php">Sell</a>
    <a href="history.php">History</a>
    <a href="deposit.php">Deposit</a>
    <a href="logout.php"><strong>Log Out</strong></a>


<table class="table table-striped">

    <thead>
        <tr>
            <th>Symbol</th>
            <th>Name</th>
            <th>Shares</th>
            <th>Price</th>
            <th>TOTAL</th>
        </tr>
    </thead>

    <tbody>
        <?php 
            if(isset($positions))
          
                foreach($positions as $position): ?>
           <tr>
                <td><?= $position["symbol"] ?></td>
                <td><?= $position["name"] ?></td>
                <td><?= $position["shares"] ?></td>
                <td><?= $position["price"] ?></td>
                <td><?= $position["total"] ?></td>
            </tr>
      <? endforeach ?>
            <tr>
                <td> CASH </td>
                <td><?=$cash?></td>
            </tr>
           
      

    </tbody>

</table>
