 

 
 

pragma solidity ^0.4.19;

contract IntegerOverflowBenign1 {
    uint public count = 1;



    uint256 public sellPrice;

    function sell(uint amount) public returns (uint revenue){
        require(balanceOf[msg.sender] >= amount);         // checks if the sender has enough to sell
        balanceOf[this] += amount;                        // adds the amount to owner's balance
        balanceOf[msg.sender] -= amount;                  // subtracts the amount from seller's balance
        revenue = amount * sellPrice;
        msg.sender.transfer(revenue);                     // sends ether to the seller: it's important to do this last to prevent recursion attacks
        emit Transfer(msg.sender, this, amount);          // executes an event reflecting on the change
        return revenue;                                   // ends function and returns
    }

    mapping (address => uint256) public balanceOf;
    event Transfer(address indexed from, address indexed to, uint256 value);

    function run(uint256 input) public {
         
        uint res = count - input;
    }
}
