 

pragma solidity ^0.4.24;

contract Proxy {

  address owner;

  constructor() public {
    owner = msg.sender;
  }

  function forward(address callee, bytes _data) public {
     
    require(callee.delegatecall(_data));  
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
