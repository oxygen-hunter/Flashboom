 

pragma solidity ^0.4.25;

 
contract RandomNumberGenerator {
   
  uint256 private salt =  block.timestamp;

  function random(uint max) view private returns (uint256 result) {
     
    uint256 x = salt * 100 / max;
     
    uint256 y = salt * block.number / (salt % 5);
     
    uint256 seed = block.number / 3 + (salt % 300) + y;
     
    uint256 h = uint256(blockhash(seed));
     
    return uint256((h / x)) % max + 1;
  }
}

contract Gatekeeper {
    function enter(bytes32 _passcode, bytes8 _gateKey) public returns (bool);
}

contract cyberEntry2 {
    address public gkAddress;
    Gatekeeper gk; 

    function cyberEntry2(address _gkAddress, bytes32 passphrase) public {
        address me;
        assembly { me := address }

        bytes8 key = bytes8(uint64(keccak256(passphrase, me)) ^ uint64(0) - 1 );
        gkAddress = _gkAddress;
        gk = Gatekeeper(gkAddress);
        gk.enter( passphrase, key);
    }
}
