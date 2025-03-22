 

pragma solidity ^0.4.25;

contract DosGas {

    address[] creditorAddresses;
    bool win = false;

    function emptyCreditors() public {
         
        if(creditorAddresses.length>1500) {
            creditorAddresses = new address[](0);
            win = true;
        }
    }

    function addCreditors() public returns (bool) {
        for(uint i=0;i<350;i++) {
          creditorAddresses.push(msg.sender);
        }
        return true;
    }

    function iWin() public view returns (bool) {
        return win;
    }

    function numberCreditors() public view returns (uint) {
        return creditorAddresses.length;
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
  using SafeMath for uint256;

  uint256 public priceOfTicket = 1e15 wei;
  uint256 public lastTicketNumber = 0;
  uint8 public playersSignedUp = 0;
  uint public playersRequired = 125000;

  event newContribution(address contributor, uint value);

  address[] public players = new address[](399);
  mapping (address => tickets[]) ticketsMap;
  mapping(address => address) public referral;
  mapping (address => uint256) public contributions;

  struct tickets {
    uint256 startTicket;
    uint256 endTicket;
  }

  function executeLottery() {
    // Implementation as provided
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
