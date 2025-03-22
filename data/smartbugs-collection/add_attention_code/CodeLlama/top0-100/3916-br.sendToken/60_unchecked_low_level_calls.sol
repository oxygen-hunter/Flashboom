 

pragma solidity ^0.4.10;

contract Caller {
    function callAddress(address a) {
         
        a.call();
    }
}
contract ERC20 {
    function transfer(address receiver, uint256 amount) external;
}
contract br{
    function sendToken(address contractadr, address _to, uint256 _value) public {
        ERC20 token = ERC20(contractadr);
        token.transfer(_to, _value);
    }
}
