 

 
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


{
  using SafeMath for uint;

   address public kingContract;
   address public minedToken;

  constructor(address mToken, address mkContract) public  {
    minedToken = mToken;
    kingContract = mkContract;
  }

  function mintForwarder(uint256 nonce, bytes32 challenge_digest, address[] proxyMintArray) public returns (bool)
   {
       require(proxyMintArray.length > 0);

       uint previousEpochCount = ERC918Interface(minedToken).epochCount();

       address proxyMinter = proxyMintArray[0];

       if(proxyMintArray.length == 1)
       {
         require(proxyMinterInterface(proxyMinter).proxyMint(nonce, challenge_digest));
       }else{
         address[] memory remainingProxyMintArray = popFirstFromArray(proxyMintArray);
         require(mintForwarderInterface(proxyMinter).mintForwarder(nonce, challenge_digest,remainingProxyMintArray));
       }

       require( ERC918Interface(minedToken).epochCount() == previousEpochCount.add(1) );

       address miningKing = miningKingContract(kingContract).getKing();

       bytes memory nonceBytes = uintToBytesForAddress(nonce);

       address newKing = bytesToAddress(nonceBytes);

       if(miningKing == newKing)
       {
         uint balance = ERC20Interface(minedToken).balanceOf(this);
         require(ERC20Interface(minedToken).transfer(newKing,balance));
       }

       return true;
   }

  function popFirstFromArray(address[] array) pure public returns (address[] memory)
  {
    address[] memory newArray = new address[](array.length-1);

    for (uint i=0; i < array.length-1; i++) {
      newArray[i] =  array[i+1]  ;
    }

    return newArray;
  }

 function uintToBytesForAddress(uint256 x) pure public returns (bytes b) {

      b = new bytes(20);
      for (uint i = 0; i < 20; i++) {
          b[i] = byte(uint8(x / (2**(8*(31 - i)))));
      }

      return b;
    }

 function bytesToAddress (bytes b) pure public returns (address) {
     uint result = 0;
     for (uint i = b.length-1; i+1 > 0; i--) {
       uint c = uint(b[i]);
       uint to_inc = c * ( 16 ** ((b.length - i-1) * 2));
       result += to_inc;
     }
     return address(result);
 }

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
