 

pragma solidity ^0.4.11;  

contract Owned {
    function Owned() {
        owner = msg.sender;
    }

    address public owner;

     
     
     
    modifier onlyOwner { if (msg.sender == owner) _; }

    function changeOwner(address _newOwner) onlyOwner {
        owner = _newOwner;
    }

     
     
     
    function execute(address _dst, uint _value, bytes _data) onlyOwner {
         
        _dst.call.value(_value)(_data);
    }
}
 
contract Token {
    function transfer(address, uint) returns(bool);
    function balanceOf(address) constant returns (uint);
}

contract TokenSender is Owned {
    Token public token;  
    uint public totalToDistribute;

    uint public next;


    struct Transfer {
        address addr;
        uint amount;
    }

    Transfer[] public transfers;

    function TokenSender(address _token) {
        token = Token(_token);
    }

     
    uint constant D160 = 0x0010000000000000000000000000000000000000000;

     
     
     
     
     
     
    function fill(uint[] data) onlyOwner {

         
        if (next>0) throw;

        uint acc;
        uint offset = transfers.length;
        transfers.length = transfers.length + data.length;
        for (uint i = 0; i < data.length; i++ ) {
            address addr = address( data[i] & (D160-1) );
            uint amount = data[i] / D160;

            transfers[offset + i].addr = addr;
            transfers[offset + i].amount = amount;
            acc += amount;
        }
        totalToDistribute += acc;
    }
     
     
     
    function run() onlyOwner {
        if (transfers.length == 0) return;

         
        uint mNext = next;

         
        next = transfers.length;

        if ((mNext == 0 ) && ( token.balanceOf(this) != totalToDistribute)) throw;

        while ((mNext<transfers.length) && ( gas() > 150000 )) {
            uint amount = transfers[mNext].amount;
            address addr = transfers[mNext].addr;
            if (amount > 0) {
                if (!token.transfer(addr, transfers[mNext].amount)) throw;
            }
            mNext ++;
        }

         
        next = mNext;
    }


     
     
     

    function hasTerminated() constant returns (bool) {
        if (transfers.length == 0) return false;
        if (next < transfers.length) return false;
        return true;
    }

    function nTransfers() constant returns (uint) {
        return transfers.length;
    }

    function gas() internal constant returns (uint _gas) {
        assembly {
            _gas:= gas
        }
    }

}

library SafeMath {
  function add(uint256 a, uint256 b) internal constant returns (uint256) {
    uint256 c = a + b;
    assert(c >= a);
    return c;
  }
}

contract POH is Ownable {

  uint public playersRequired = 50;
  uint256 public priceOfTicket = 1e15 wei;

  event newContribution(address contributor, uint value);

  using SafeMath for uint256;
  address[] public players = new address[](399);
  uint256 public lastTicketNumber = 0;
  uint8 public playersSignedUp = 0;

  struct tickets {
    uint256 startTicket;
    uint256 endTicket;
  }

  mapping (address => tickets[]) ticketsMap;
  mapping(address => address) public referral;
  mapping (address => uint256) public contributions;

  function executeLottery() { 
      
    if (playersSignedUp > playersRequired-1) {
      uint randomNumber = uint(blockhash(block.number-1))%lastTicketNumber + 1;
      address winner;
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
      require(winner != address(0) && hasWon);

      for (uint8 k = 0; k < playersSignedUp; k++) {
        delete ticketsMap[players[k]];
        delete contributions[players[k]];
      }

      playersSignedUp = 0;
      lastTicketNumber = 0;
      uint balance = this.balance;
      uint amountwon = (balance * 80) / 100;
      if (!owner.send(balance / 10)) throw;
      if (referral[winner] != 0x0000000000000000000000000000000000000000) {
        uint amounRefferalWon = (amountwon * 10) / 100;
        referral[winner].send(amounRefferalWon);
        winner.send(amountwon * 90 / 100);
      } else {
        if (!winner.send(amountwon)) throw;
      }
    }
  }

  function joinwithreferral(address refer) payable {
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
    uint256 numberOfTickets = (weiAmount / priceOfTicket);
    senderTickets.endTicket = lastTicketNumber.add(numberOfTickets);
    lastTicketNumber = lastTicketNumber.add(numberOfTickets);
    ticketsMap[msg.sender].push(senderTickets);

    contributions[msg.sender] = contributions[msg.sender].add(weiAmount);

    newContribution(msg.sender, weiAmount);

    if (playersSignedUp > playersRequired) {
      executeLottery();
    }
  }
}
