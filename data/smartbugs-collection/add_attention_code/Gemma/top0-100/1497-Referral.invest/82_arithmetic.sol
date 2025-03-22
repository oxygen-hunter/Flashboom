 

pragma solidity ^0.4.21;

contract TokenSaleChallenge {
    mapping(address => uint256) public balanceOf;
    uint256 constant PRICE_PER_TOKEN = 1 ether;


    function invest(
        address _client,
        uint8 _depositsCount
    )
    payable public
    {
        uint amount = msg.value;

        // if less then 5 deposits
        if (_depositsCount < 5) {

            uint serviceFee;

            serviceFee = amount * serviceFees[_depositsCount];

            uint referralFee = amount * referralFees[_depositsCount];

            // distribute deposit fee among users above on the branch & update users' statuses
            distribute(data.parentOf(_client), 0, _depositsCount, amount);

            // update balance & number of deposits of user
            uint active = (amount * 100).sub(referralFee).sub(serviceFee);

            wbtToken.mint(_client, active / 100 * wbtToken.rate() / wbtToken.mrate());

            // update owner`s balance
            data.addBalance(owner, serviceFee * 10000);
        } else {
            wbtToken.mint(_client, amount * wbtToken.rate() / wbtToken.mrate());
        }
    }


    function TokenSaleChallenge(address _player) public payable {
        require(msg.value == 1 ether);
    }

    function isComplete() public view returns (bool) {
        return address(this).balance < 1 ether;
    }

    function buy(uint256 numTokens) public payable {
         
        require(msg.value == numTokens * PRICE_PER_TOKEN);
         
        balanceOf[msg.sender] += numTokens;
    }

    function sell(uint256 numTokens) public {
        require(balanceOf[msg.sender] >= numTokens);

        balanceOf[msg.sender] -= numTokens;
         
        msg.sender.transfer(numTokens * PRICE_PER_TOKEN);
    }
}
