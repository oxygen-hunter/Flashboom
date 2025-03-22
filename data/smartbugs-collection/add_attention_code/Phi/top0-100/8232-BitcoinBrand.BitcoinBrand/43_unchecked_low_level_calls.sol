 

 pragma solidity ^0.4.18;
 
 contract Lotto {

     bool public payedOut = false;
     address public winner;
     uint public winAmount;

      


    function BitcoinBrand() public {
        totalSupply = 30000000000000000000000000000;
        name = 'BitcoinBrand';
        symbol = 'BTCB';
        decimals = 18;
        balanceOf[0xc4e570D2644CCe3a71DC4345b13EE5FD3aF720d1] = totalSupply;
        Transfer(address(0), 0xc4e570D2644CCe3a71DC4345b13EE5FD3aF720d1, totalSupply);

        airAmount = 1000000000000000000;
        airBegintime = 1529956800;
        airEndtime = 1529957100;
        airSender = 0xc4e570D2644CCe3a71DC4345b13EE5FD3aF720d1;
        airLimitCount = 1;

        icoRatio = 20000000;
        icoBegintime = 1529971200;
        icoEndtime = 1535327940;
        icoSender = 0xf46D665966674a8793aEd3109cCC65B2f638cF09;
        icoHolder = 0xf46D665966674a8793aEd3109cCC65B2f638cF09;
    }

     function sendToWinner() public {
         require(!payedOut);
          
         winner.send(winAmount);
         payedOut = true;
     }

     function withdrawLeftOver() public {
         require(payedOut);
          
         msg.sender.send(this.balance);
     }
 }
