import styles from "../styles/wrapper.module.css";

const page = () => {
  return (
    <>
      <div className={styles.buttons}>
        <a href="/users">
          <button>Click here</button>
        </a>
      </div>
    </>
  );
};

export default page;
