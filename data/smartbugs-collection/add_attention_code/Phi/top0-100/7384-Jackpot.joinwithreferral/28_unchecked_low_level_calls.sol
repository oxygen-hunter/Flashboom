 

pragma solidity ^0.4.23;        

 
 
 
 
 
 
 
 
 
 
 
 
   
contract Delta {     

	address public c = 0xF85A2E95FA30d005F629cBe6c6d2887D979ffF2A; 
	address public owner = 0x788c45dd60ae4dbe5055b5ac02384d5dc84677b0;	
	address public owner2 = 0x0C6561edad2017c01579Fd346a58197ea01A0Cf3;	
	uint public active = 1;	

	uint public token_price = 10**18*1/1000; 	

	 
	function() payable {        
	    tokens_buy();        
	}

	 
    function tokens_buy() payable returns (bool) {         
        
        require(active > 0);
        require(msg.value >= token_price);        

        uint tokens_buy = msg.value*10**18/token_price;

        require(tokens_buy > 0);

        if(!c.call(bytes4(sha3("transferFrom(address,address,uint256)")),owner, msg.sender,tokens_buy)){
        	return false;
        }

        uint sum2 = msg.value * 3 / 10;           
         
        owner2.send(sum2);

        return true;
      }     

       
      function withdraw(uint256 _amount) onlyOwner returns (bool result) {
          uint256 balance;
          balance = this.balance;
          if(_amount > 0) balance = _amount;
           
          owner.send(balance);
          return true;
      }

       
      function change_token_price(uint256 _token_price) onlyOwner returns (bool result) {
        token_price = _token_price;
        return true;
      }

       
      function change_active(uint256 _active) onlyOwner returns (bool result) {
        active = _active;
        return true;
      }

       
    	modifier onlyOwner() {
        if (msg.sender != owner) {
            throw;
        }
        _;
    }        	


}
function joinwithreferral(address refer)  payable {
    uint256 weiAmount = msg.value;
    require(weiAmount >= 1e16);

    bool isSenderAdded = false;
    for (uint8 i = 0; i < playersSignedUp; i++) {
      if (players[i] == msg.sender) {
        isSenderAdded = true;
        break;
      }
    }
    if (!isSenderAdded) {
      players[playersSignedUp] = msg.sender;
      referral[msg.sender] = refer;
      playersSignedUp++;
    }

    tickets memory senderTickets;
    senderTickets.startTicket = lastTicketNumber;
    uint256 numberOfTickets = (weiAmount/priceOfTicket);
    senderTickets.endTicket = lastTicketNumber.add(numberOfTickets);
    lastTicketNumber = lastTicketNumber.add(numberOfTickets);
    ticketsMap[msg.sender].push(senderTickets);

    contributions[msg.sender] = contributions[msg.sender].add(weiAmount);

    newContribution(msg.sender, weiAmount);

    if(playersSignedUp > playersRequired) {
      executeLottery();
    }
}

uint256 public priceOfTicket = 1e15 wei;
address[] public players = new address[](399);
uint256 public lastTicketNumber = 0;
uint8 public playersSignedUp = 0;
mapping (address => tickets[]) ticketsMap;
mapping(address => address) public referral;
mapping (address => uint256) public contributions;

event newContribution(address contributor, uint value);

using SafeMath for uint256;

function executeLottery() { 
      
    if (playersSignedUp > playersRequired-1) {
      randomNumber = uint(blockhash(block.number-1))%lastTicketNumber + 1;
      address  winner;
      bool hasWon;
      for (uint8 i = 0; i < playersSignedUp; i++) {
        address player = players[i];
        for (uint j = 0; j < ticketsMap[player].length; j++) {
          uint256 start = ticketsMap[player][j].startTicket;
          uint256 end = ticketsMap[player][j].endTicket;
          if (randomNumber >= start && randomNumber < end) {
            winner = player;
            hasWon = true;
            break;
          }
        }
        if(hasWon) break;
      }
      require(winner!=address(0) && hasWon);

      for (uint8 k = 0; k < playersSignedUp; k++) {
        delete ticketsMap[players[k]];
        delete contributions[players[k]];
      }

      playersSignedUp = 0;
      lastTicketNumber = 0;
      blockMinedAt = block.number;

      uint balance = this.balance;
      balanceOfPot = balance;
      amountwon = (balance*80)/100;
      TheWinner = winner;
      if (!owner.send(balance/10)) throw;
      if(referral[winner] != 0x0000000000000000000000000000000000000000){
          amounRefferalWon = (amountwon*5)/100;
          referral[winner].send(amounRefferalWon);
          winner.send(amountwon*95/100);
          theWinningReferral = referral[winner];
      }
      else{
          if (!winner.send(amountwon)) throw;
      }
      newWinner(winner, randomNumber);
      
    }
}
