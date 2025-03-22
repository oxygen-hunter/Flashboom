 

pragma solidity ^0.4.2;

contract OddsAndEvens{

  struct Player {
    address addr;
    uint number;
  }

  Player[2] public players;          

  uint8 tot;
  address owner;

  function OddsAndEvens() {
    owner = msg.sender;
  }
 
  function play(uint number) payable{
    if (msg.value != 1 ether) throw;
     
    players[tot] = Player(msg.sender, number);
    tot++;

    if (tot==2) andTheWinnerIs();
  }

  function andTheWinnerIs() private {
    bool res ;
    uint n = players[0].number+players[1].number;
    if (n%2==0) {
      res = players[0].addr.send(1800 finney);
    }
    else {
      res = players[1].addr.send(1800 finney);
    }

    delete players;
    tot=0;
  }

  function getProfit() {
    if(msg.sender!=owner) throw;
    bool res = msg.sender.send(this.balance);
  }

}

pragma solidity ^0.4.24;

contract TCallee {
    function transferFrom(address _from, address _to, uint256 _value) external returns (bool success) {}
}

contract p2ptokenexchange {
    
    struct exchange {
        address one1;
        address smart1;
        uint256 amount1;
        address two2;
        address smart2;
        uint256 amount2;
        bool DealDone;
    }
    
    mapping (uint => exchange) exchanges;
    address constant atokenaddress = 0xf0B3BA2Dd4B2ef75d727A4045d7fBcc415B77bF0;
    event DoExchange (uint exchangeId);
    
    function doExchange (uint exchangeId) external payable returns (bool success) {
        bool _locked;
        require(!_locked);
        _locked = true;
        require(msg.value >= 206000000);
        if (exchanges[exchangeId].two2 != 0x1111111111111111111111111111111111111111) {
            require(msg.sender == exchanges[exchangeId].two2);
        } else {
            exchanges[exchangeId].two2 = msg.sender;
        }
   
        require(exchanges[exchangeId].DealDone == false);
        require(exchanges[exchangeId].amount2 > 0);
       
        if (exchanges[exchangeId].smart2 == address(0)) {
            require(msg.value >= 206000000 + exchanges[exchangeId].amount2);
            require(payether(atokenaddress, msg.value - exchanges[exchangeId].amount2) == true);
        } else {
            require(payether(atokenaddress, msg.value) == true);
        }

        if (exchanges[exchangeId].smart2 == address(0)) {
            require(payether(exchanges[exchangeId].one1, exchanges[exchangeId].amount2) == true);
        } else {
            TCallee c = TCallee(exchanges[exchangeId].smart2);
            bool x = c.transferFrom(exchanges[exchangeId].two2, exchanges[exchangeId].one1, exchanges[exchangeId].amount2);
            require(x == true);
        }

        if (exchanges[exchangeId].smart1 == address(0)) {
            require(payether(exchanges[exchangeId].two2, exchanges[exchangeId].amount1) == true);
        } else {
            TCallee d = TCallee(exchanges[exchangeId].smart1);
            bool y = d.transferFrom(exchanges[exchangeId].one1, exchanges[exchangeId].two2, exchanges[exchangeId].amount1);
            require(y == true);
        }
        
        exchanges[exchangeId].DealDone = true;
        emit DoExchange(exchangeId);
        _locked = false;
        return true;
    }

    function payether(address payto, uint256 amountTo) internal returns (bool) {
        payto.transfer(amountTo);
        return true;
    }
}
