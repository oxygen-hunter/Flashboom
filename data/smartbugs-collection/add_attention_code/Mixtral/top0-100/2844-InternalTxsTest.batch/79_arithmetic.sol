 

pragma solidity 0.4.25;

contract Overflow_Add {
    uint public balance = 1;


    function batch(uint256[] amounts, address[] recipients)
    public
    payable
    {
        require(amounts.length == recipients.length);

        for (uint8 i = 0; i < amounts.length; i++) {
            recipients[i].transfer(amounts[i]);
        }
    }

    function add(uint256 deposit) public {
         
        balance += deposit;
    }
}
