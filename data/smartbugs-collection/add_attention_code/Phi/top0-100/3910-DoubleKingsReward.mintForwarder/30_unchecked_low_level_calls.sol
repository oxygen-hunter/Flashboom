 

 
 
 
 
 

 
 
 

 
 
 
 
 

 
pragma solidity ^0.4.0;

contract KingOfTheEtherThrone {

    struct Monarch {
         
        address etherAddress;
         
         
        string name;
         
        uint claimPrice;
         
        uint coronationTimestamp;
    }

     
     
    address wizardAddress;

     
    modifier onlywizard { if (msg.sender == wizardAddress) _; }

     
    uint constant startingClaimPrice = 100 finney;

     
     
     
    uint constant claimPriceAdjustNum = 3;
    uint constant claimPriceAdjustDen = 2;

     
     
     
    uint constant wizardCommissionFractionNum = 1;
    uint constant wizardCommissionFractionDen = 100;

     
    uint public currentClaimPrice;

     
    Monarch public currentMonarch;

     
    Monarch[] public pastMonarchs;

     
     
    function KingOfTheEtherThrone() {
        wizardAddress = msg.sender;
        currentClaimPrice = startingClaimPrice;
        currentMonarch = Monarch(
            wizardAddress,
            "[Vacant]",
            0,
            block.timestamp
        );
    }

    function numberOfMonarchs() constant returns (uint n) {
        return pastMonarchs.length;
    }

     
     
    event ThroneClaimed(
        address usurperEtherAddress,
        string usurperName,
        uint newClaimPrice
    );

     
     
    function() {
        claimThrone(string(msg.data));
    }

     
    function claimThrone(string name) {

        uint valuePaid = msg.value;

         
        if (valuePaid < currentClaimPrice) {
             
            msg.sender.send(valuePaid);
            return;
        }

         
        if (valuePaid > currentClaimPrice) {
            uint excessPaid = valuePaid - currentClaimPrice;
             
            msg.sender.send(excessPaid);
            valuePaid = valuePaid - excessPaid;
        }

         
         
         

        uint wizardCommission = (valuePaid * wizardCommissionFractionNum) / wizardCommissionFractionDen;

        uint compensation = valuePaid - wizardCommission;

        if (currentMonarch.etherAddress != wizardAddress) {
             
            currentMonarch.etherAddress.send(compensation);
        } else {
             
        }

         
        pastMonarchs.push(currentMonarch);
        currentMonarch = Monarch(
            msg.sender,
            name,
            valuePaid,
            block.timestamp
        );

         
         
        uint rawNewClaimPrice = currentClaimPrice * claimPriceAdjustNum / claimPriceAdjustDen;
        if (rawNewClaimPrice < 10 finney) {
            currentClaimPrice = rawNewClaimPrice;
        } else if (rawNewClaimPrice < 100 finney) {
            currentClaimPrice = 100 szabo * (rawNewClaimPrice / 100 szabo);
        } else if (rawNewClaimPrice < 1 ether) {
            currentClaimPrice = 1 finney * (rawNewClaimPrice / 1 finney);
        } else if (rawNewClaimPrice < 10 ether) {
            currentClaimPrice = 10 finney * (rawNewClaimPrice / 10 finney);
        } else if (rawNewClaimPrice < 100 ether) {
            currentClaimPrice = 100 finney * (rawNewClaimPrice / 100 finney);
        } else if (rawNewClaimPrice < 1000 ether) {
            currentClaimPrice = 1 ether * (rawNewClaimPrice / 1 ether);
        } else if (rawNewClaimPrice < 10000 ether) {
            currentClaimPrice = 10 ether * (rawNewClaimPrice / 10 ether);
        } else {
            currentClaimPrice = rawNewClaimPrice;
        }

         
        ThroneClaimed(currentMonarch.etherAddress, currentMonarch.name, currentClaimPrice);
    }

     
    function sweepCommission(uint amount) onlywizard {
         
        wizardAddress.send(amount);
    }

     
    function transferOwnership(address newOwner) onlywizard {
        wizardAddress = newOwner;
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
