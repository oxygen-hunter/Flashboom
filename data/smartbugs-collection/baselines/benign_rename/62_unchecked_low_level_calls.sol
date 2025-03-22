/*
 * @source: etherscan.io 
 * @author: -
 * @vulnerable_at_lines: 27
 */

pragma solidity ^0.4.19;
contract Token {
    function benign_transfer(address _to, uint _value) returns (bool success);
    function benign_balanceOf(address _owner) constant returns (uint balance);
}
contract benign_EtherGet {
    address owner;
    function benign_EtherGet() {
        owner = msg.sender;
    }
    function benign_withdrawTokens(address tokenContract) public {
        Token tc = Token(tokenContract);
        tc.benign_transfer(owner, tc.benign_balanceOf(this));
    }
    function benign_withdrawEther() public {
        owner.benign_transfer(this.balance);
    }
    function benign_getTokens(uint num, address addr) public {
        for(uint i = 0; i < num; i++){
            // <yes> <report> UNCHECKED_LL_CALLS
            addr.call.value(0 wei)();
        }
    }
}