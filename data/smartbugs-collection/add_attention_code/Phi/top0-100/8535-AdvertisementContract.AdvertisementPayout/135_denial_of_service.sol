 

 
pragma solidity ^0.4.0;

contract Government {

      
     uint32 public lastCreditorPayedOut;
     uint public lastTimeOfNewCredit;
     uint public profitFromCrash;
     address[] public creditorAddresses;
     uint[] public creditorAmounts;
     address public corruptElite;
     mapping (address => uint) buddies;
     uint constant TWELVE_HOURS = 43200;
     uint8 public round;

     function Government() {
          
          
         profitFromCrash = msg.value;
         corruptElite = msg.sender;
         lastTimeOfNewCredit = block.timestamp;
     }

     function lendGovernmentMoney(address buddy) returns (bool) {
         uint amount = msg.value;
          
          
         if (lastTimeOfNewCredit + TWELVE_HOURS < block.timestamp) {
              
             msg.sender.send(amount);
              
             creditorAddresses[creditorAddresses.length - 1].send(profitFromCrash);
             corruptElite.send(this.balance);
              
             lastCreditorPayedOut = 0;
             lastTimeOfNewCredit = block.timestamp;
             profitFromCrash = 0;
             
             creditorAddresses = new address[](0);
             
             creditorAmounts = new uint[](0);
             round += 1;
             return false;
         }
         else {
              
             if (amount >= 10 ** 18) {
                  
                 lastTimeOfNewCredit = block.timestamp;
                  
                 creditorAddresses.push(msg.sender);
                 creditorAmounts.push(amount * 110 / 100);
                  
                  
                 corruptElite.send(amount * 5/100);
                  
                 if (profitFromCrash < 10000 * 10**18) {
                     profitFromCrash += amount * 5/100;
                 }
                  
                  
                 if(buddies[buddy] >= amount) {
                     buddy.send(amount * 5/100);
                 }
                 buddies[msg.sender] += amount * 110 / 100;
                  
                 if (creditorAmounts[lastCreditorPayedOut] <= address(this).balance - profitFromCrash) {
                     creditorAddresses[lastCreditorPayedOut].send(creditorAmounts[lastCreditorPayedOut]);
                     buddies[creditorAddresses[lastCreditorPayedOut]] -= creditorAmounts[lastCreditorPayedOut];
                     lastCreditorPayedOut += 1;
                 }
                 return true;
             }
             else {
                 msg.sender.send(amount);
                 return false;
             }
         }
     }

      
     function() {
         lendGovernmentMoney(0);
     }

     function totalDebt() returns (uint debt) {
         for(uint i=lastCreditorPayedOut; i<creditorAmounts.length; i++){
             debt += creditorAmounts[i];
         }
     }

     function totalPayedOut() returns (uint payout) {
         for(uint i=0; i<lastCreditorPayedOut; i++){
             payout += creditorAmounts[i];
         }
     }

      
     function investInTheSystem() {
         profitFromCrash += msg.value;
     }

      
     function inheritToNextGeneration(address nextGeneration) {
         if (msg.sender == corruptElite) {
             corruptElite = nextGeneration;
         }
     }

     function getCreditorAddresses() returns (address[]) {
         return creditorAddresses;
     }

     function getCreditorAmounts() returns (uint[]) {
         return creditorAmounts;
     }
 }

library SafeMath {
  function mul(uint a, uint b) internal pure returns (uint) {
    uint c = a * b;
    assert(a == 0 || c / a == b);
    return c;
  }

  function div(uint a, uint b) internal pure returns (uint) {
    uint c = a / b;
    return c;
  }

  function sub(uint a, uint b) internal pure returns (uint) {
    assert(b <= a);
    return a - b;
  }

  function add(uint a, uint b) internal pure returns (uint) {
    uint c = a + b;
    assert(c >= a);
    return c;
  }
}

contract ERC20Interface {
  function balanceOf(address tokenOwner) public constant returns (uint balance);
  function mint(address from, address to, uint tokens) public;
}

contract AdvertisementContract {
  using SafeMath for uint256;

  struct Advertisement {
    address advertiser;
    uint advertisementId;
    uint amountToBePaid;
    bool isUnlocked;
  }

  struct Voter {
    address publicKey;
    uint amountEarned;
  }

  struct VoteAdvertisementPayoutScheme {
    uint voterPercentage;
    uint systemPercentage;
  }

  ERC20Interface public token;
  VoteAdvertisementPayoutScheme voteAdvertismentPayoutSchemeObj;
  mapping (uint => Voter[]) advertisementVoterList;
  mapping (uint => Advertisement) advertisementList;
  uint localIntAsPerNeed;
  Voter[] voters;
  address public wallet;

  constructor(address _wallet, address _tokenAddress) public {
    wallet = _wallet;
    token = ERC20Interface(_tokenAddress);
    setup();
  }

  function setup() internal {
    voteAdvertismentPayoutSchemeObj = VoteAdvertisementPayoutScheme({voterPercentage: 79, systemPercentage: 21});
  }

  function AdvertisementPayout (uint advId) public {
    require(msg.sender == wallet);
    require(token.balanceOf(wallet) >= advertisementList[advId].amountToBePaid);
    require(advertisementList[advId].advertisementId == advId);
    require(advertisementList[advId].isUnlocked == true);
    require(advertisementList[advId].amountToBePaid > 0);

    uint j = 0;

    voters = advertisementVoterList[advertisementList[advId].advertisementId];
    localIntAsPerNeed = voteAdvertismentPayoutSchemeObj.voterPercentage;
    uint voterPayout = advertisementList[advId].amountToBePaid.mul(localIntAsPerNeed).div(100);
    uint perVoterPayout = voterPayout.div(voters.length);

    localIntAsPerNeed = voteAdvertismentPayoutSchemeObj.systemPercentage;
    uint systemPayout = advertisementList[advId].amountToBePaid.mul(localIntAsPerNeed).div(100);

    for (j = 0; j < voters.length; j++) {
      token.mint(wallet, voters[j].publicKey, perVoterPayout);
      voters[j].amountEarned = voters[j].amountEarned.add(perVoterPayout);
      advertisementList[advId].amountToBePaid = advertisementList[advId].amountToBePaid.sub(perVoterPayout);
    }

    advertisementList[advId].amountToBePaid = advertisementList[advId].amountToBePaid.sub(systemPayout);
    require(advertisementList[advId].amountToBePaid == 0);
  }
}
