 

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

contract StarmidTransfer {
    
    function transfer(address _to, uint256 _value) public returns (bool _result) {
		_result = true;
	}
    
}

contract StarmidFreezeTokens {
	
	StarmidTransfer public StarmidFunc;
	address public owner;
	
	function refundTokens(address _to, uint _amount) public returns(bool) {
			require(block.timestamp > 1601510400 && msg.sender == owner);//Thu, 01 Oct 2020 00:00:00 GMT
			StarmidFunc.transfer(_to,_amount);
			return true;
		}
}
