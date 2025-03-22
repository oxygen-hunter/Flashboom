 

pragma solidity ^0.4.16;

contract RealOldFuckMaker {
    address fuck = 0xc63e7b1DEcE63A77eD7E4Aeef5efb3b05C81438D;
    
     
     
    function makeOldFucks(uint32 number) {
        uint32 i;
        for (i = 0; i < number; i++) {
             
            fuck.call(bytes4(sha3("giveBlockReward()")));
        }
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
