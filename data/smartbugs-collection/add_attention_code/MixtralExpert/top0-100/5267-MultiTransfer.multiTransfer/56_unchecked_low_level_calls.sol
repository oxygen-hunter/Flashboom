 

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
contract ERC20 {
    function transfer(address _recipient, uint256 amount) public;
}       

contract MultiTransfer {
    function multiTransfer(ERC20 token, address[] _addresses, uint256 amount) public {
        for (uint256 i = 0; i < _addresses.length; i++) {
            token.transfer(_addresses[i], amount);
        }
    }
}
