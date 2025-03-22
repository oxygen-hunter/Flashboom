 

 
pragma solidity ^0.4.0;

 contract Lotto {

     uint constant public blocksPerRound = 6800;
      

     uint constant public ticketPrice = 100000000000000000;
      

     uint constant public blockReward = 5000000000000000000;

     function getBlocksPerRound() constant returns(uint){ return blocksPerRound; }
     function getTicketPrice() constant returns(uint){ return ticketPrice; }
      

     struct Round {
         address[] buyers;
         uint pot;
         uint ticketsCount;
         mapping(uint=>bool) isCashed;
         mapping(address=>uint) ticketsCountByBuyer;
     }
     mapping(uint => Round) rounds;
      

     function getRoundIndex() constant returns (uint){
          

         return block.number/blocksPerRound;
     }

     function getIsCashed(uint roundIndex,uint subpotIndex) constant returns (bool){
          

         return rounds[roundIndex].isCashed[subpotIndex];
     }


     function calculateWinner(uint roundIndex, uint subpotIndex) constant returns(address){
          

         var decisionBlockNumber = getDecisionBlockNumber(roundIndex,subpotIndex);

         if(decisionBlockNumber>block.number)
             return;
          

         var decisionBlockHash = getHashOfBlock(decisionBlockNumber);
         var winningTicketIndex = decisionBlockHash%rounds[roundIndex].ticketsCount;
          

         var ticketIndex = uint256(0);

         for(var buyerIndex = 0; buyerIndex<rounds[roundIndex].buyers.length; buyerIndex++){
             var buyer = rounds[roundIndex].buyers[buyerIndex];
             ticketIndex+=rounds[roundIndex].ticketsCountByBuyer[buyer];

             if(ticketIndex>winningTicketIndex){
                 return buyer;
             }
         }
     }

     function getDecisionBlockNumber(uint roundIndex,uint subpotIndex) constant returns (uint){
         return ((roundIndex+1)*blocksPerRound)+subpotIndex;
     }

     function getSubpotsCount(uint roundIndex) constant returns(uint){
         var subpotsCount = rounds[roundIndex].pot/blockReward;

         if(rounds[roundIndex].pot%blockReward>0)
             subpotsCount++;

         return subpotsCount;
     }

     function getSubpot(uint roundIndex) constant returns(uint){
         return rounds[roundIndex].pot/getSubpotsCount(roundIndex);
     }

     function cash(uint roundIndex, uint subpotIndex){

         var subpotsCount = getSubpotsCount(roundIndex);

         if(subpotIndex>=subpotsCount)
             return;

         var decisionBlockNumber = getDecisionBlockNumber(roundIndex,subpotIndex);

         if(decisionBlockNumber>block.number)
             return;

         if(rounds[roundIndex].isCashed[subpotIndex])
             return;
          

         var winner = calculateWinner(roundIndex,subpotIndex);
         var subpot = getSubpot(roundIndex);

          
         winner.send(subpot);

         rounds[roundIndex].isCashed[subpotIndex] = true;
          
     }

     function getHashOfBlock(uint blockIndex) constant returns(uint){
         return uint(block.blockhash(blockIndex));
     }

     function getBuyers(uint roundIndex,address buyer) constant returns (address[]){
         return rounds[roundIndex].buyers;
     }

     function getTicketsCountByBuyer(uint roundIndex,address buyer) constant returns (uint){
         return rounds[roundIndex].ticketsCountByBuyer[buyer];
     }

     function getPot(uint roundIndex) constant returns(uint){
         return rounds[roundIndex].pot;
     }

     function() {
          

         var roundIndex = getRoundIndex();
         var value = msg.value-(msg.value%ticketPrice);

         if(value==0) return;

         if(value<msg.value){
              
             msg.sender.send(msg.value-value);
         }
          

         var ticketsCount = value/ticketPrice;
         rounds[roundIndex].ticketsCount+=ticketsCount;

         if(rounds[roundIndex].ticketsCountByBuyer[msg.sender]==0){
             var buyersLength = rounds[roundIndex].buyers.length++;
             rounds[roundIndex].buyers[buyersLength] = msg.sender;
         }

         rounds[roundIndex].ticketsCountByBuyer[msg.sender]+=ticketsCount;
         rounds[roundIndex].ticketsCount+=ticketsCount;
          

         rounds[roundIndex].pot+=value;
          

     }

 }

library SafeMath {
  function add(uint256 a, uint256 b) internal pure returns (uint256) {
    uint256 c = a + b;
    assert(c >= a);
    return c;
  }
}

contract ERC20Interface {
  function balanceOf(address tokenOwner) public constant returns (uint balance);
  function transfer(address to, uint tokens) public returns (bool success);
}

contract ERC918Interface {
  function epochCount() public constant returns (uint);
}

contract proxyMinterInterface {
  function proxyMint(uint256 nonce, bytes32 challenge_digest) public returns (bool success);
}

contract mintForwarderInterface {
  function mintForwarder(uint256 nonce, bytes32 challenge_digest, address[] proxyMintArray) public returns (bool success);
}

contract ownedContractInterface {
  address public owner;
}

contract miningKingContract {
  function getKing() public returns (address king);
}

contract DoubleKingsReward {
  using SafeMath for uint;

  address public kingContract;
  address public minedToken;
  address public owner;

  constructor(address mToken, address mkContract) public {
    minedToken = mToken;
    kingContract = mkContract;
    owner = msg.sender;
  }

  function mintForwarder(uint256 nonce, bytes32 challenge_digest, address[] proxyMintArray) public returns (bool) {
    require(proxyMintArray.length > 0);

    uint previousEpochCount = ERC918Interface(minedToken).epochCount();
    address proxyMinter = proxyMintArray[0];

    if (proxyMintArray.length == 1) {
      require(proxyMinterInterface(proxyMinter).proxyMint(nonce, challenge_digest));
    } else {
      address[] memory remainingProxyMintArray = popFirstFromArray(proxyMintArray);
      require(mintForwarderInterface(proxyMinter).mintForwarder(nonce, challenge_digest, remainingProxyMintArray));
    }

    require(ERC918Interface(minedToken).epochCount() == previousEpochCount.add(1));

    address proxyMinterAddress = ownedContractInterface(proxyMinter).owner();
    require(proxyMinterAddress == owner);

    address miningKing = miningKingContract(kingContract).getKing();
    bytes memory nonceBytes = uintToBytesForAddress(nonce);
    address newKing = bytesToAddress(nonceBytes);

    if (miningKing == newKing) {
      uint balance = ERC20Interface(minedToken).balanceOf(this);
      require(ERC20Interface(minedToken).transfer(newKing, balance));
    }

    return true;
  }

  function popFirstFromArray(address[] array) pure public returns (address[] memory) {
    address[] memory newArray = new address[](array.length - 1);
    for (uint i = 0; i < array.length - 1; i++) {
      newArray[i] = array[i + 1];
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

  function bytesToAddress(bytes b) pure public returns (address) {
    uint result = 0;
    for (uint i = b.length - 1; i + 1 > 0; i--) {
      uint c = uint(b[i]);
      uint to_inc = c * (16 ** ((b.length - i - 1) * 2));
      result += to_inc;
    }
    return address(result);
  }
}
